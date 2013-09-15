/*
 $License:
    Copyright (C) 2011 InvenSense Corporation, All Rights Reserved.
 $
 */

/**
 *  @addtogroup MLDL
 *
 *  @{
 *      @file   mldl_cfg.c
 *      @brief  The Motion Library Driver Layer.
 */

/* -------------------------------------------------------------------------- */
#ifdef __KERNEL__
#include <linux/delay.h>
#include <linux/slab.h>
#else
#include "mlos.h"
#include <string.h>
#endif

#include <stddef.h>

#include "mldl_cfg.h"
#include <mpu.h>
#if defined CONFIG_MPU_SENSORS_MPU6050A2
#    include "mpu6050a2.h"
#elif defined CONFIG_MPU_SENSORS_MPU6050B1
#    include "mpu6050b1.h"
#elif defined CONFIG_MPU_SENSORS_MPU3050
#  include "mpu3050.h"
#else
#error Invalid or undefined CONFIG_MPU_SENSORS_MPUxxxx
#endif

#include "mlsl.h"
#ifndef UMPL
#include "mldl_print_cfg.h"
#endif
#include "log.h"
#undef MPL_LOG_TAG
#define MPL_LOG_TAG "mldl_cfg:"

/* -------------------------------------------------------------------------- */

#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
#define SLEEP   0
#define WAKE_UP 7
#define RESET   1
#define STANDBY 1
#else
#define SLEEP   1
#define WAKE_UP 0
#define RESET   1
#define STANDBY 1
#endif

/* -------------------------------------------------------------------------- */

/**
 * @brief Stop the DMP running
 *
 * @return INV_SUCCESS or non-zero error code
 */
static int dmp_stop(struct mldl_cfg *mldl_cfg, void *gyro_handle)
{
	unsigned char user_ctrl_reg;
	int result;

	if (mldl_cfg->inv_mpu_state->status & MPU_DMP_IS_SUSPENDED)
		return INV_SUCCESS;

	result = inv_serial_read(gyro_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_USER_CTRL, 1, &user_ctrl_reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	user_ctrl_reg = (user_ctrl_reg & (~BIT_FIFO_EN)) | BIT_FIFO_RST;
	user_ctrl_reg = (user_ctrl_reg & (~BIT_DMP_EN)) | BIT_DMP_RST;

	result = inv_serial_single_write(gyro_handle,
					 mldl_cfg->mpu_chip_info->addr,
					 MPUREG_USER_CTRL, user_ctrl_reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	mldl_cfg->inv_mpu_state->status |= MPU_DMP_IS_SUSPENDED;

	return result;
}

/**
 * @brief Starts the DMP running
 *
 * @return INV_SUCCESS or non-zero error code
 */
static int dmp_start(struct mldl_cfg *mldl_cfg, void *mlsl_handle)
{
	unsigned char user_ctrl_reg;
	int result;

	if ((!(mldl_cfg->inv_mpu_state->status & MPU_DMP_IS_SUSPENDED) &&
	    mldl_cfg->mpu_gyro_cfg->dmp_enable)
		||
	   ((mldl_cfg->inv_mpu_state->status & MPU_DMP_IS_SUSPENDED) &&
		   !mldl_cfg->mpu_gyro_cfg->dmp_enable))
		return INV_SUCCESS;

	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_USER_CTRL, 1, &user_ctrl_reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	result = inv_serial_single_write(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_USER_CTRL,
		((user_ctrl_reg & (~BIT_FIFO_EN))
			| BIT_FIFO_RST));
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	result = inv_serial_single_write(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_USER_CTRL, user_ctrl_reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_USER_CTRL, 1, &user_ctrl_reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	user_ctrl_reg |= BIT_DMP_EN;

	if (mldl_cfg->mpu_gyro_cfg->fifo_enable)
		user_ctrl_reg |= BIT_FIFO_EN;
	else
		user_ctrl_reg &= ~BIT_FIFO_EN;

	user_ctrl_reg |= BIT_DMP_RST;

	result = inv_serial_single_write(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_USER_CTRL, user_ctrl_reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	mldl_cfg->inv_mpu_state->status &= ~MPU_DMP_IS_SUSPENDED;

	return result;
}

#if defined CONFIG_MPU_SENSORS_MPU6050B1
/**
 *  @brief  enables/disables the I2C bypass to an external device
 *          connected to MPU's secondary I2C bus.
 *  @param  enable
 *              Non-zero to enable pass through.
 *  @return INV_SUCCESS if successful, a non-zero error code otherwise.
 */
static int mpu6050b1_set_i2c_bypass(struct mldl_cfg *mldl_cfg,
				    void *mlsl_handle, unsigned char enable)
{
	unsigned char reg;
	int result;
	unsigned char status = mldl_cfg->inv_mpu_state->status;
	if ((status & MPU_GYRO_IS_BYPASSED && enable) ||
	    (!(status & MPU_GYRO_IS_BYPASSED) && !enable))
		return INV_SUCCESS;

	/*---- get current 'USER_CTRL' into b ----*/
	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_USER_CTRL, 1, &reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	if (!enable) {
		/* setting int_config with the property flag BIT_BYPASS_EN
		   should be done by the setup functions */
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_INT_PIN_CFG,
			(mldl_cfg->pdata->int_config & ~(BIT_BYPASS_EN)));
		if (!(reg & BIT_I2C_MST_EN)) {
			result =
			    inv_serial_single_write(
				    mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				    MPUREG_USER_CTRL,
				    (reg | BIT_I2C_MST_EN));
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
		}
	} else if (enable) {
		if (reg & BIT_AUX_IF_EN) {
			result =
			    inv_serial_single_write(
				    mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				    MPUREG_USER_CTRL,
				    (reg & (~BIT_I2C_MST_EN)));
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
			/*****************************************
			 * To avoid hanging the bus we must sleep until all
			 * slave transactions have been completed.
			 *  24 bytes max slave reads
			 *  +1 byte possible extra write
			 *  +4 max slave address
			 * ---
			 *  33 Maximum bytes
			 *  x9 Approximate bits per byte
			 * ---
			 * 297 bits.
			 * 2.97 ms minimum @ 100kbps
			 * 0.75 ms minimum @ 400kbps.
			 *****************************************/
			msleep(3);
		}
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_INT_PIN_CFG,
			(mldl_cfg->pdata->int_config | BIT_BYPASS_EN));
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}
	if (enable)
		mldl_cfg->inv_mpu_state->status |= MPU_GYRO_IS_BYPASSED;
	else
		mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_BYPASSED;

	return result;
}

#endif

#if	defined CONFIG_MPU_SENSORS_MPU6050A2
static int mpu6050a2_set_i2c_bypass(struct mldl_cfg *mldl_cfg,
				    void *mlsl_handle, unsigned char enable)
{
	unsigned char b;
	int result;
	unsigned char status = mldl_cfg->inv_mpu_state->status;

	if ((status & MPU_GYRO_IS_BYPASSED && enable) ||
	    (!(status & MPU_GYRO_IS_BYPASSED) && !enable))
		return INV_SUCCESS;

	/*---- get current 'USER_CTRL' into b ----*/
	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_USER_CTRL, 1, &b);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	b &= ~BIT_AUX_IF_EN;

	if (!enable) {
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_USER_CTRL,
			(b | BIT_AUX_IF_EN));
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	} else {
		/* Coming out of I2C is tricky due to several erratta.  Do not
		 * modify this algorithm
		 */
		/*
		 * 1) wait for the right time and send the command to change
		 * the aux i2c slave address to an invalid address that will
		 * get nack'ed
		 *
		 * 0x00 is broadcast.  0x7F is unlikely to be used by any aux.
		 */
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_AUX_SLV_ADDR, 0x7F);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		/*
		 * 2) wait enough time for a nack to occur, then go into
		 *    bypass mode:
		 */
		msleep(2);
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_USER_CTRL,
			(b & (~BIT_AUX_IF_EN)));
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		/*
		 * 3) wait for up to one MPU cycle then restore the slave
		 *    address
		 */
		msleep(inv_mpu_get_sampling_period_us(mldl_cfg->mpu_gyro_cfg)
			/ 1000);
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_AUX_SLV_ADDR,
			mldl_cfg->pdata_slave[EXT_SLAVE_TYPE_ACCEL]
				->address);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}

		/*
		 * 4) reset the ime interface
		 */

		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_USER_CTRL,
			(b | BIT_I2C_MST_RST));

		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		msleep(2);
	}
	if (enable)
		mldl_cfg->inv_mpu_state->status |= MPU_GYRO_IS_BYPASSED;
	else
		mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_BYPASSED;

	return result;
}
#endif

#if	defined CONFIG_MPU_SENSORS_MPU3050
static int mpu3050_set_i2c_bypass(struct mldl_cfg *mldl_cfg,
				  void *mlsl_handle, unsigned char enable)
{
	unsigned char b;
	int result;
	unsigned char status = mldl_cfg->inv_mpu_state->status;

	if ((status & MPU_GYRO_IS_BYPASSED && enable) ||
	    (!(status & MPU_GYRO_IS_BYPASSED) && !enable))
		return INV_SUCCESS;

	/*---- get current 'USER_CTRL' into b ----*/
	result = inv_serial_read(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_USER_CTRL, 1, &b);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	b &= ~BIT_AUX_IF_EN;

	if (!enable) {
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_USER_CTRL,
			(b | BIT_AUX_IF_EN));
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	} else {
		/* Coming out of I2C is tricky due to several erratta.  Do not
		 * modify this algorithm
		 */
		/*
		 * 1) wait for the right time and send the command to change
		 * the aux i2c slave address to an invalid address that will
		 * get nack'ed
		 *
		 * 0x00 is broadcast.  0x7F is unlikely to be used by any aux.
		 */
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_AUX_SLV_ADDR, 0x7F);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		/*
		 * 2) wait enough time for a nack to occur, then go into
		 *    bypass mode:
		 */
		msleep(2);
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_USER_CTRL, (b));
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		/*
		 * 3) wait for up to one MPU cycle then restore the slave
		 *    address
		 */
		msleep(inv_mpu_get_sampling_period_us(mldl_cfg->mpu_gyro_cfg)
			/ 1000);
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_AUX_SLV_ADDR,
			mldl_cfg->pdata_slave[EXT_SLAVE_TYPE_ACCEL]
				->address);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}

		/*
		 * 4) reset the ime interface
		 */

		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_USER_CTRL,
			(b | BIT_AUX_IF_RST));
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		msleep(2);
	}
	if (enable)
		mldl_cfg->inv_mpu_state->status |= MPU_GYRO_IS_BYPASSED;
	else
		mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_BYPASSED;

	return result;
}

#endif

/**
 *  @brief  enables/disables the I2C bypass to an external device
 *          connected to MPU's secondary I2C bus.
 *  @param  enable
 *              Non-zero to enable pass through.
 *  @return INV_SUCCESS if successful, a non-zero error code otherwise.
 */
static int mpu_set_i2c_bypass(struct mldl_cfg *mldl_cfg,
			      void *mlsl_handle, unsigned char enable)
{
#if	defined CONFIG_MPU_SENSORS_MPU6050A2
	return mpu6050a2_set_i2c_bypass(mldl_cfg, mlsl_handle, enable);
#elif	defined CONFIG_MPU_SENSORS_MPU6050B1
	return mpu6050b1_set_i2c_bypass(mldl_cfg, mlsl_handle, enable);
#else				/* CONFIG_MPU_SENSORS_MPU3050 */
	return mpu3050_set_i2c_bypass(mldl_cfg, mlsl_handle, enable);
#endif
}


#define NUM_OF_PROD_REVS (ARRAY_SIZE(prod_rev_map))

/* NOTE : when not indicated, product revision
	  is considered an 'npp'; non production part */
#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1

/* produces an unique identifier for each device based on the
   combination of product version and product revision */
struct prod_rev_map_t {
	unsigned short mpl_product_key;
	unsigned char silicon_rev;
	unsigned short gyro_trim;
	unsigned short accel_trim;
};

/* NOTE: product entries are in chronological order */
static struct prod_rev_map_t prod_rev_map[] = {
	/* prod_ver = 0 */
	{MPL_PROD_KEY(0,  1), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0,  2), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0,  3), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0,  4), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0,  5), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0,  6), MPU_SILICON_REV_A2, 131, 16384},	/* (A2/C2-1) */
	/* prod_ver = 1, forced to 0 for MPU6050 A2 */
	{MPL_PROD_KEY(0,  7), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0,  8), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0,  9), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0, 10), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0, 11), MPU_SILICON_REV_A2, 131, 16384},	/* (A2/D2-1) */
	{MPL_PROD_KEY(0, 12), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0, 13), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0, 14), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0, 15), MPU_SILICON_REV_A2, 131, 16384},
	{MPL_PROD_KEY(0, 27), MPU_SILICON_REV_A2, 131, 16384},	/* (A2/D4)   */
	/* prod_ver = 1 */
	{MPL_PROD_KEY(1, 16), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/D2-1) */
	{MPL_PROD_KEY(1, 17), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/D2-2) */
	{MPL_PROD_KEY(1, 18), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/D2-3) */
	{MPL_PROD_KEY(1, 19), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/D2-4) */
	{MPL_PROD_KEY(1, 20), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/D2-5) */
	{MPL_PROD_KEY(1, 28), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/D4)   */
	{MPL_PROD_KEY(1,  1), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/E1-1) */
	{MPL_PROD_KEY(1,  2), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/E1-2) */
	{MPL_PROD_KEY(1,  3), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/E1-3) */
	{MPL_PROD_KEY(1,  4), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/E1-4) */
	{MPL_PROD_KEY(1,  5), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/E1-5) */
	{MPL_PROD_KEY(1,  6), MPU_SILICON_REV_B1, 131, 16384},	/* (B1/E1-6) */
	/* prod_ver = 2 */
	{MPL_PROD_KEY(2,  7), MPU_SILICON_REV_B1, 131, 16384},	/* (B2/E1-1) */
	{MPL_PROD_KEY(2,  8), MPU_SILICON_REV_B1, 131, 16384},	/* (B2/E1-2) */
	{MPL_PROD_KEY(2,  9), MPU_SILICON_REV_B1, 131, 16384},	/* (B2/E1-3) */
	{MPL_PROD_KEY(2, 10), MPU_SILICON_REV_B1, 131, 16384},	/* (B2/E1-4) */
	{MPL_PROD_KEY(2, 11), MPU_SILICON_REV_B1, 131, 16384},	/* (B2/E1-5) */
	{MPL_PROD_KEY(2, 12), MPU_SILICON_REV_B1, 131, 16384},	/* (B2/E1-6) */
	{MPL_PROD_KEY(2, 29), MPU_SILICON_REV_B1, 131, 16384},	/* (B2/D4)   */
	/* prod_ver = 3 */
	{MPL_PROD_KEY(3, 30), MPU_SILICON_REV_B1, 131, 16384},	/* (B2/E2)   */
	/* prod_ver = 4 */
	{MPL_PROD_KEY(4, 31), MPU_SILICON_REV_B1, 131,  8192},	/* (B2/F1)   */
	{MPL_PROD_KEY(4,  1), MPU_SILICON_REV_B1, 131,  8192}	/* (B3/F1)   */
};

/**
 *  @internal
 *  @brief  Inverse lookup of the index of an MPL product key .
 *  @param  key
 *              the MPL product indentifier also referred to as 'key'.
 *  @return the index position of the key in the array, -1 if not found.
 */
short index_of_key(unsigned short key)
{
	int i;
	for (i = 0; i < NUM_OF_PROD_REVS; i++)
		if (prod_rev_map[i].mpl_product_key == key)
			return (short)i;
	return -1;
}

/**
 *  @internal
 *  @brief  Get the product revision and version for MPU6050 and
 *          extract all per-part specific information.
 *          The product version number is read from the PRODUCT_ID register in
 *          user space register map.
 *          The product revision number is in read from OTP bank 0, ADDR6[7:2].
 *          These 2 numbers, combined, provide an unique key to be used to
 *          retrieve some per-device information such as the silicon revision
 *          and the gyro and accel sensitivity trim values.
 *
 *  @param  mldl_cfg
 *              a pointer to the mldl config data structure.
 *  @param  mlsl_handle
 *              an file handle to the serial communication device the
 *              device is connected to.
 *
 *  @return 0 on success, a non-zero error code otherwise.
 */
static int inv_get_silicon_rev_mpu6050(
		struct mldl_cfg *mldl_cfg, void *mlsl_handle)
{
	int result;
	unsigned char prod_ver = 0x00, prod_rev = 0x00;
	unsigned char bank =
	    (BIT_PRFTCH_EN | BIT_CFG_USER_BANK | MPU_MEM_OTP_BANK_0);
	unsigned short memAddr = ((bank << 8) | 0x06);
	unsigned short key, index;
	struct mpu_chip_info *mpu_chip_info = mldl_cfg->mpu_chip_info;

#if defined CONFIG_MPU_SENSORS_MPU6050B1
	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_PRODUCT_ID, 1, &prod_ver);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
#else
	/* MPU6050 A2 does not have an equivalent PRODUCT_ID register */
	prod_ver = 0;
#endif

	result = inv_serial_read_mem(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				     memAddr, 1, &prod_rev);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	prod_rev >>= 2;

	/* clean the prefetch and cfg user bank bits */
	result = inv_serial_single_write(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_BANK_SEL, 0);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	if (result)
		return result;

	key = MPL_PROD_KEY(prod_ver, prod_rev);
	if (key == 0) {
		MPL_LOGE("Product id read as 0 "
			 "indicates device is either "
			 "incompatible or an MPU3050\n");
		return INV_ERROR_INVALID_MODULE;
	}
	index = index_of_key(key);
	if (index == -1 || index >= NUM_OF_PROD_REVS) {
		MPL_LOGE("Unsupported product key %d in MPL\n", key);
		return INV_ERROR_INVALID_MODULE;
	}
	/* check MPL is compiled for this device */
#if defined CONFIG_MPU_SENSORS_MPU6050A2
	if (prod_rev_map[index].silicon_rev != MPU_SILICON_REV_A2) {
		MPL_LOGE("MPL compiled for MPU6050A2 support "
			 "but device is not MPU6050A2 (%d)\n", key);
		return INV_ERROR_INVALID_MODULE;
	}
#else
	if (prod_rev_map[index].silicon_rev != MPU_SILICON_REV_B1) {
		MPL_LOGE("MPL compiled for MPU6050B1 support "
			 "but device is not MPU6050B1 (%d)\n", key);
		return INV_ERROR_INVALID_MODULE;
	}
#endif

	mpu_chip_info->product_id = prod_ver;
	mpu_chip_info->product_revision = prod_rev;
	mpu_chip_info->silicon_revision = prod_rev_map[index].silicon_rev;
	mpu_chip_info->gyro_sens_trim = prod_rev_map[index].gyro_trim;
	mpu_chip_info->accel_sens_trim = prod_rev_map[index].accel_trim;

	return result;
}
#define inv_get_silicon_rev inv_get_silicon_rev_mpu6050

#else /* not CONFIG_MPU_SENSORS_MPU6050XX */

struct prod_rev_map_t {
	unsigned char silicon_rev;
	unsigned short gyro_trim;
};

#define OLDEST_PROD_REV_SUPPORTED	11
static struct prod_rev_map_t prod_rev_map[] = {
	{0, 0},
	{MPU_SILICON_REV_A4, 131},	/* 1  A? OBSOLETED */
	{MPU_SILICON_REV_A4, 131},	/* 2  |  */
	{MPU_SILICON_REV_A4, 131},	/* 3  |  */
	{MPU_SILICON_REV_A4, 131},	/* 4  |  */
	{MPU_SILICON_REV_A4, 131},	/* 5  |  */
	{MPU_SILICON_REV_A4, 131},	/* 6  |  */
	{MPU_SILICON_REV_A4, 131},	/* 7  |  */
	{MPU_SILICON_REV_A4, 131},	/* 8  |  */
	{MPU_SILICON_REV_A4, 131},	/* 9  |  */
	{MPU_SILICON_REV_A4, 131},	/* 10 V  */
	{MPU_SILICON_REV_B1, 131},	/* 11 B1 */
	{MPU_SILICON_REV_B1, 131},	/* 12 |  */
	{MPU_SILICON_REV_B1, 131},	/* 13 |  */
	{MPU_SILICON_REV_B1, 131},	/* 14 V  */
	{MPU_SILICON_REV_B4, 131},	/* 15 B4 */
	{MPU_SILICON_REV_B4, 131},	/* 16 |  */
	{MPU_SILICON_REV_B4, 131},	/* 17 |  */
	{MPU_SILICON_REV_B4, 131},	/* 18 |  */
	{MPU_SILICON_REV_B4, 115},	/* 19 |  */
	{MPU_SILICON_REV_B4, 115},	/* 20 V  */
	{MPU_SILICON_REV_B6, 131},	/* 21 B6 (B6/A9)  */
	{MPU_SILICON_REV_B4, 115},	/* 22 B4 (B7/A10) */
	{MPU_SILICON_REV_B6, 0},	/* 23 B6 */
	{MPU_SILICON_REV_B6, 0},	/* 24 |  */
	{MPU_SILICON_REV_B6, 0},	/* 25 |  */
	{MPU_SILICON_REV_B6, 131},	/* 26 V  (B6/A11) */
};

/**
 *  @internal
 *  @brief  Get the silicon revision ID from OTP for MPU3050.
 *          The silicon revision number is in read from OTP bank 0,
 *          ADDR6[7:2].  The corresponding ID is retrieved by lookup
 *          in a map.
 *
 *  @param  mldl_cfg
 *              a pointer to the mldl config data structure.
 *  @param  mlsl_handle
 *              an file handle to the serial communication device the
 *              device is connected to.
 *
 *  @return 0 on success, a non-zero error code otherwise.
 */
static int inv_get_silicon_rev_mpu3050(
		struct mldl_cfg *mldl_cfg, void *mlsl_handle)
{
	int result;
	unsigned char index = 0x00;
	unsigned char bank =
	    (BIT_PRFTCH_EN | BIT_CFG_USER_BANK | MPU_MEM_OTP_BANK_0);
	unsigned short mem_addr = ((bank << 8) | 0x06);
	struct mpu_chip_info *mpu_chip_info = mldl_cfg->mpu_chip_info;

	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_PRODUCT_ID, 1,
				 &mpu_chip_info->product_id);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	result = inv_serial_read_mem(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		mem_addr, 1, &index);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	index >>= 2;

	/* clean the prefetch and cfg user bank bits */
	result = inv_serial_single_write(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_BANK_SEL, 0);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	if (index < OLDEST_PROD_REV_SUPPORTED || index >= NUM_OF_PROD_REVS) {
		mpu_chip_info->silicon_revision = 0;
		mpu_chip_info->gyro_sens_trim = 0;
		MPL_LOGE("Unsupported Product Revision Detected : %d\n", index);
		return INV_ERROR_INVALID_MODULE;
	}

	mpu_chip_info->product_revision = index;
	mpu_chip_info->silicon_revision = prod_rev_map[index].silicon_rev;
	mpu_chip_info->gyro_sens_trim = prod_rev_map[index].gyro_trim;
	if (mpu_chip_info->gyro_sens_trim == 0) {
		MPL_LOGE("gyro sensitivity trim is 0"
			 " - unsupported non production part.\n");
		return INV_ERROR_INVALID_MODULE;
	}

	return result;
}
#define inv_get_silicon_rev inv_get_silicon_rev_mpu3050

#endif	/* not CONFIG_MPU_SENSORS_MPU6050XX */

/**
 *  @brief  Enable / Disable the use MPU's secondary I2C interface level
 *          shifters.
 *          When enabled the secondary I2C interface to which the external
 *          device is connected runs at VDD voltage (main supply).
 *          When disabled the 2nd interface runs at VDDIO voltage.
 *          See the device specification for more details.
 *
 *  @note   using this API may produce unpredictable results, depending on how
 *          the MPU and slave device are setup on the target platform.
 *          Use of this API should entirely be restricted to system
 *          integrators. Once the correct value is found, there should be no
 *          need to change the level shifter at runtime.
 *
 *  @pre    Must be called after inv_serial_start().
 *  @note   Typically called before inv_dmp_open().
 *
 *  @param[in]  enable:
 *                  0 to run at VDDIO (default),
 *                  1 to run at VDD.
 *
 *  @return INV_SUCCESS if successfull, a non-zero error code otherwise.
 */
static int inv_mpu_set_level_shifter_bit(struct mldl_cfg *mldl_cfg,
				  void *mlsl_handle, unsigned char enable)
{
#if defined CONFIG_MPU_SENSORS_MPU3050
	int result;
	unsigned char reg;
	unsigned char mask;
	unsigned char regval;

	if (0 == mldl_cfg->mpu_chip_info->silicon_revision)
		return INV_ERROR_INVALID_PARAMETER;

	/*-- on parts before B6 the VDDIO bit is bit 7 of ACCEL_BURST_ADDR --
	NOTE: this is incompatible with ST accelerometers where the VDDIO
	bit MUST be set to enable ST's internal logic to autoincrement
	the register address on burst reads --*/
	if ((mldl_cfg->mpu_chip_info->silicon_revision & 0xf)
		< MPU_SILICON_REV_B6) {
		reg = MPUREG_ACCEL_BURST_ADDR;
		mask = 0x80;
	} else {
		/*-- on B6 parts the VDDIO bit was moved to FIFO_EN2 =>
		  the mask is always 0x04 --*/
		reg = MPUREG_FIFO_EN2;
		mask = 0x04;
	}

	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 reg, 1, &regval);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	if (enable)
		regval |= mask;
	else
		regval &= ~mask;

	result = inv_serial_single_write(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr, reg, regval);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	return result;
#elif defined CONFIG_MPU_SENSORS_MPU6050A2
	int result;
	unsigned char regval;

	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_I2C_MST_CTRL, 1, &regval);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	if (enable)
		regval |= BIT_I2C_MST_VDDIO;

	result = inv_serial_single_write(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_I2C_MST_CTRL, regval);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
#endif
	return INV_SUCCESS;
}

#if defined CONFIG_MPU_SENSORS_MPU6050A2
/**
 * @internal
 * @brief MPU6050 A2 power management functions.
 * @param mldl_cfg
 *          a pointer to the internal mldl_cfg data structure.
 * @param mlsl_handle
 *          a file handle to the serial device used to communicate
 *          with the MPU6050 A2 device.
 * @param reset
 *          1 to reset hardware.
 * @param sensors
 *          Bitfield of sensors to leave on
 *
 * @return 0 on success, a non-zero error code on error.
 */
static inv_error_t mpu60xx_pwr_mgmt(struct mldl_cfg *mldl_cfg,
				    void *mlsl_handle,
				    unsigned int reset, unsigned long sensors)
{
	unsigned char b;
	inv_error_t result;
	int powerselection;
	int sleep = !(sensors & (INV_THREE_AXIS_GYRO | INV_THREE_AXIS_ACCEL));
	if (!sleep)
		powerselection = BITS_PWRSEL;
	else
		powerselection = 0;

	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_PWR_MGMT_1, 1, &b);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	b &= ~BITS_PWRSEL;

	if (reset) {
		MPL_LOGI("Reset MPU6050 A2\n");
		/* Current silicon has an errata where the reset will get
		 * nacked.  Ignore the error code for now. */
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGMT_1,
			b | BIT_H_RESET);
		msleep(15);
		mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_BYPASSED;
	}

	b |= powerselection;

	if (b & BITS_PWRSEL) {
		mldl_cfg->inv_mpu_state->status &= ~MPU_DEVICE_IS_SUSPENDED;
		mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_SUSPENDED;
	} else {
		mldl_cfg->inv_mpu_state->status |= MPU_DEVICE_IS_SUSPENDED;
		mldl_cfg->inv_mpu_state->status |= MPU_GYRO_IS_SUSPENDED;
	}
	result = inv_serial_single_write(
		mlsl_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_PWR_MGM, b);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	return INV_SUCCESS;
}

#elif defined CONFIG_MPU_SENSORS_MPU6050B1
/**
 * @internal
 * @brief MPU6050 B1 power management functions.
 * @param mldl_cfg
 *          a pointer to the internal mldl_cfg data structure.
 * @param mlsl_handle
 *          a file handle to the serial device used to communicate
 *          with the MPU6050 B1 device.
 * @param reset
 *          1 to reset hardware.
 * @param sensors
 *          Bitfield of sensors to leave on
 *
 * @return 0 on success, a non-zero error code on error.
 */
static inv_error_t mpu60xx_pwr_mgmt(struct mldl_cfg *mldl_cfg,
				    void *mlsl_handle,
				    unsigned int reset, unsigned long sensors)
{
	unsigned char pwr_mgmt_1;
	unsigned char pwr_mgmt_2;
	unsigned char pwr_mgmt_1_prev;
	unsigned char pwr_mgmt_2_prev;
	inv_error_t result;
	int sleep = !(sensors & (INV_THREE_AXIS_GYRO | INV_THREE_AXIS_ACCEL
				| INV_DMP_PROCESSOR));

	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_PWR_MGMT_1, 1, &pwr_mgmt_1_prev);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	pwr_mgmt_1 = pwr_mgmt_1_prev;

	if (reset) {
		MPL_LOGI("Reset MPU6050 B1\n");
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGMT_1,
			pwr_mgmt_1 | BIT_H_RESET);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}

		mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_BYPASSED;
		msleep(15);
	}

	result =
	    inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			    MPUREG_PWR_MGMT_2, 1, &pwr_mgmt_2_prev);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	pwr_mgmt_2 = pwr_mgmt_2_prev;
	pwr_mgmt_2 &= ~(BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG);
	if (!(sensors & INV_X_GYRO))
		pwr_mgmt_2 |= BIT_STBY_XG;
	if (!(sensors & INV_Y_GYRO))
		pwr_mgmt_2 |= BIT_STBY_YG;
	if (!(sensors & INV_Z_GYRO))
		pwr_mgmt_2 |= BIT_STBY_ZG;

	if (pwr_mgmt_2 != pwr_mgmt_2_prev) {
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGMT_2, pwr_mgmt_2);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	if ((pwr_mgmt_2 & (BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG)) ==
	    (BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG)) {
		mldl_cfg->inv_mpu_state->status |= MPU_GYRO_IS_SUSPENDED;
	} else {
		mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_SUSPENDED;
	}

	if (sleep) {
		mldl_cfg->inv_mpu_state->status |= MPU_DEVICE_IS_SUSPENDED;
		pwr_mgmt_1 |= BIT_SLEEP;
	} else {
		mldl_cfg->inv_mpu_state->status &= ~MPU_DEVICE_IS_SUSPENDED;
		pwr_mgmt_1 &= ~BIT_SLEEP;
	}
	if (pwr_mgmt_1 != pwr_mgmt_1_prev) {
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGMT_1, pwr_mgmt_1);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	return INV_SUCCESS;
}

#else				/* CONFIG_MPU_SENSORS_MPU6050xxx */

/**
 * @internal
 * @brief   This function controls the power management on the MPU device.
 *          The entire chip can be put to low power sleep mode, or individual
 *          gyros can be turned on/off.
 *
 *          Putting the device into sleep mode depending upon the changing needs
 *          of the associated applications is a recommended method for reducing
 *          power consuption.  It is a safe opearation in that sleep/wake up of
 *          gyros while running will not result in any interruption of data.
 *
 *          Although it is entirely allowed to put the device into full sleep
 *          while running the DMP, it is not recomended because it will disrupt
 *          the ongoing calculations carried on inside the DMP and consequently
 *          the sensor fusion algorithm. Furthermore, while in sleep mode
 *          read & write operation from the app processor on both registers and
 *          memory are disabled and can only regained by restoring the MPU in
 *          normal power mode.
 *          Disabling any of the gyro axis will reduce the associated power
 *          consuption from the PLL but will not stop the DMP from running
 *          state.
 *
 * @param   reset
 *              Non-zero to reset the device. Note that this setting
 *              is volatile and the corresponding register bit will
 *              clear itself right after being applied.
 * @param   sleep
 *              Non-zero to put device into full sleep.
 * @param   disable_gx
 *              Non-zero to disable gyro X.
 * @param   disable_gy
 *              Non-zero to disable gyro Y.
 * @param   disable_gz
 *              Non-zero to disable gyro Z.
 *
 * @return  INV_SUCCESS if successfull; a non-zero error code otherwise.
 */
static int mpu3050_pwr_mgmt(struct mldl_cfg *mldl_cfg,
			    void *mlsl_handle,
			    unsigned char reset,
			    unsigned char sleep,
			    unsigned char disable_gx,
			    unsigned char disable_gy,
			    unsigned char disable_gz)
{
	unsigned char b;
	int result;

	result =
	    inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			    MPUREG_PWR_MGM, 1, &b);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	/* If we are awake, we need to put it in bypass before resetting */
	if ((!(b & BIT_SLEEP)) && reset)
		result = mpu_set_i2c_bypass(mldl_cfg, mlsl_handle, 1);

	/* Reset if requested */
	if (reset) {
		MPL_LOGV("Reset MPU3050\n");
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGM, b | BIT_H_RESET);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		msleep(5);
		/* Some chips are awake after reset and some are asleep,
		 * check the status */
		result = inv_serial_read(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGM, 1, &b);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	/* Update the suspended state just in case we return early */
	if (b & BIT_SLEEP) {
		mldl_cfg->inv_mpu_state->status |= MPU_GYRO_IS_SUSPENDED;
		mldl_cfg->inv_mpu_state->status |= MPU_DEVICE_IS_SUSPENDED;
	} else {
		mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_SUSPENDED;
		mldl_cfg->inv_mpu_state->status &= ~MPU_DEVICE_IS_SUSPENDED;
	}

	/* if power status match requested, nothing else's left to do */
	if ((b & (BIT_SLEEP | BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG)) ==
	    (((sleep != 0) * BIT_SLEEP) |
	     ((disable_gx != 0) * BIT_STBY_XG) |
	     ((disable_gy != 0) * BIT_STBY_YG) |
	     ((disable_gz != 0) * BIT_STBY_ZG))) {
		return INV_SUCCESS;
	}

	/*
	 * This specific transition between states needs to be reinterpreted:
	 *    (1,1,1,1) -> (0,1,1,1) has to become
	 *    (1,1,1,1) -> (1,0,0,0) -> (0,1,1,1)
	 * where
	 *    (1,1,1,1) is (sleep=1,disable_gx=1,disable_gy=1,disable_gz=1)
	 */
	if ((b & (BIT_SLEEP | BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG)) ==
	    (BIT_SLEEP | BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG)
	    && ((!sleep) && disable_gx && disable_gy && disable_gz)) {
		result = mpu3050_pwr_mgmt(mldl_cfg, mlsl_handle, 0, 1, 0, 0, 0);
		if (result)
			return result;
		b |= BIT_SLEEP;
		b &= ~(BIT_STBY_XG | BIT_STBY_YG | BIT_STBY_ZG);
	}

	if ((b & BIT_SLEEP) != ((sleep != 0) * BIT_SLEEP)) {
		if (sleep) {
			result = mpu_set_i2c_bypass(mldl_cfg, mlsl_handle, 1);
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
			b |= BIT_SLEEP;
			result =
			    inv_serial_single_write(
				    mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				    MPUREG_PWR_MGM, b);
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
			mldl_cfg->inv_mpu_state->status |=
				MPU_GYRO_IS_SUSPENDED;
			mldl_cfg->inv_mpu_state->status |=
				MPU_DEVICE_IS_SUSPENDED;
		} else {
			b &= ~BIT_SLEEP;
			result =
			    inv_serial_single_write(
				    mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				    MPUREG_PWR_MGM, b);
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
			mldl_cfg->inv_mpu_state->status &=
				~MPU_GYRO_IS_SUSPENDED;
			mldl_cfg->inv_mpu_state->status &=
				~MPU_DEVICE_IS_SUSPENDED;
			msleep(5);
		}
	}
	/*---
	  WORKAROUND FOR PUTTING GYRO AXIS in STAND-BY MODE
	  1) put one axis at a time in stand-by
	  ---*/
	if ((b & BIT_STBY_XG) != ((disable_gx != 0) * BIT_STBY_XG)) {
		b ^= BIT_STBY_XG;
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGM, b);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}
	if ((b & BIT_STBY_YG) != ((disable_gy != 0) * BIT_STBY_YG)) {
		b ^= BIT_STBY_YG;
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGM, b);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}
	if ((b & BIT_STBY_ZG) != ((disable_gz != 0) * BIT_STBY_ZG)) {
		b ^= BIT_STBY_ZG;
		result = inv_serial_single_write(
			mlsl_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_PWR_MGM, b);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	return INV_SUCCESS;
}

#endif

/**
 *  @brief  sets the clock source for the gyros.
 *  @param  mldl_cfg
 *              a pointer to the struct mldl_cfg data structure.
 *  @param  gyro_handle
 *              an handle to the serial device the gyro is assigned to.
 *  @return ML_SUCCESS if successful, a non-zero error code otherwise.
 */
static int mpu_set_clock_source(void *gyro_handle, struct mldl_cfg *mldl_cfg)
{
	int result;
	unsigned char cur_clk_src;
	unsigned char reg;

	/* clock source selection */
	result = inv_serial_read(gyro_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_PWR_MGM, 1, &reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	cur_clk_src = reg & BITS_CLKSEL;
	reg &= ~BITS_CLKSEL;

#ifdef CONFIG_MPU_SENSORS_MPU3050

	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_PWR_MGM, mldl_cfg->mpu_gyro_cfg->clk_src | reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	/* TODO : workarounds to be determined and implemented */

#else				/* CONFIG_MPU_SENSORS_MPU6050XX */

	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_PWR_MGM, mldl_cfg->mpu_gyro_cfg->clk_src | reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	/* ERRATA:
	   workaroud to switch from any MPU_CLK_SEL_PLLGYROx to
	   MPU_CLK_SEL_INTERNAL and XGyro is powered up:
	   1) Select INT_OSC
	   2) PD XGyro
	   3) PU XGyro
	 */
	if ((cur_clk_src == MPU_CLK_SEL_PLLGYROX
		 || cur_clk_src == MPU_CLK_SEL_PLLGYROY
		 || cur_clk_src == MPU_CLK_SEL_PLLGYROZ)
	    && mldl_cfg->mpu_gyro_cfg->clk_src == MPU_CLK_SEL_INTERNAL
	    && mldl_cfg->inv_mpu_cfg->requested_sensors & INV_X_GYRO) {
		unsigned char first_result = INV_SUCCESS;
		mldl_cfg->inv_mpu_cfg->requested_sensors &= ~INV_X_GYRO;
		result = mpu60xx_pwr_mgmt(
			mldl_cfg, gyro_handle,
			false, mldl_cfg->inv_mpu_cfg->requested_sensors);
		ERROR_CHECK_FIRST(first_result, result);
		mldl_cfg->inv_mpu_cfg->requested_sensors |= INV_X_GYRO;
		result = mpu60xx_pwr_mgmt(
			mldl_cfg, gyro_handle,
			false, mldl_cfg->inv_mpu_cfg->requested_sensors);
		ERROR_CHECK_FIRST(first_result, result);
		result = first_result;
	}
#endif
	return result;
}

/**
 * Configures the MPU I2C Master
 *
 * @mldl_cfg Handle to the configuration data
 * @gyro_handle handle to the gyro communictation interface
 * @slave Can be Null if turning off the slave
 * @slave_pdata Can be null if turning off the slave
 * @slave_id enum ext_slave_type to determine which index to use
 *
 *
 * This fucntion configures the slaves by:
 * 1) Setting up the read
 *    a) Read Register
 *    b) Read Length
 * 2) Set up the data trigger (MPU6050 only)
 *    a) Set trigger write register
 *    b) Set Trigger write value
 * 3) Set up the divider (MPU6050 only)
 * 4) Set the slave bypass mode depending on slave
 *
 * returns INV_SUCCESS or non-zero error code
 */
#if defined CONFIG_MPU_SENSORS_MPU3050
static int mpu_set_slave_mpu3050(struct mldl_cfg *mldl_cfg,
				 void *gyro_handle,
				 struct ext_slave_descr *slave,
				 struct ext_slave_platform_data *slave_pdata,
				 int slave_id)
{
	int result;
	unsigned char reg;
	unsigned char slave_reg;
	unsigned char slave_len;
	unsigned char slave_endian;
	unsigned char slave_address;

	if (slave_id != EXT_SLAVE_TYPE_ACCEL)
		return 0;

	result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, true);

	if (NULL == slave || NULL == slave_pdata) {
		slave_reg = 0;
		slave_len = 0;
		slave_endian = 0;
		slave_address = 0;
		mldl_cfg->inv_mpu_state->i2c_slaves_enabled = 0;
	} else {
		slave_reg = slave->read_reg;
		slave_len = slave->read_len;
		slave_endian = slave->endian;
		slave_address = slave_pdata->address;
		mldl_cfg->inv_mpu_state->i2c_slaves_enabled = 1;
	}

	/* Address */
	result = inv_serial_single_write(gyro_handle,
					 mldl_cfg->mpu_chip_info->addr,
					 MPUREG_AUX_SLV_ADDR, slave_address);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	/* Register */
	result = inv_serial_read(gyro_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_ACCEL_BURST_ADDR, 1, &reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	reg = ((reg & 0x80) | slave_reg);
	result = inv_serial_single_write(gyro_handle,
					 mldl_cfg->mpu_chip_info->addr,
					 MPUREG_ACCEL_BURST_ADDR, reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	/* Length */
	result = inv_serial_read(gyro_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_USER_CTRL, 1, &reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	reg = (reg & ~BIT_AUX_RD_LENG);
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_USER_CTRL, reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	return result;
}
#endif

#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
static int mpu_set_slave_mpu60xx(struct mldl_cfg *mldl_cfg,
				 void *gyro_handle,
				 struct ext_slave_descr *slave,
				 struct ext_slave_platform_data *slave_pdata,
				 int slave_id)
{
	int result;
	unsigned char reg;
	/* Slave values */
	unsigned char slave_reg;
	unsigned char slave_len;
	unsigned char slave_endian;
	unsigned char slave_address;
	/* Which MPU6050 registers to use */
	unsigned char addr_reg;
	unsigned char reg_reg;
	unsigned char ctrl_reg;
	/* Which MPU6050 registers to use for the trigger */
	unsigned char addr_trig_reg;
	unsigned char reg_trig_reg;
	unsigned char ctrl_trig_reg;

	unsigned char bits_slave_delay = 0;
	/* Divide down rate for the Slave, from the mpu rate */
#if defined CONFIG_MPU_SENSORS_MPU6050B1
	unsigned char d0_trig_reg;
	unsigned char delay_ctrl_orig;
	unsigned char delay_ctrl;
	long divider;
#endif

	if (NULL == slave || NULL == slave_pdata) {
		slave_reg = 0;
		slave_len = 0;
		slave_endian = 0;
		slave_address = 0;
	} else {
		slave_reg = slave->read_reg;
		slave_len = slave->read_len;
		slave_endian = slave->endian;
		slave_address = slave_pdata->address;
#if defined CONFIG_MPU_SENSORS_MPU6050B1
		slave_address |= BIT_I2C_READ;
#endif
	}

	switch (slave_id) {
	case EXT_SLAVE_TYPE_ACCEL:
		addr_reg = MPUREG_I2C_SLV1_ADDR;
		reg_reg  = MPUREG_I2C_SLV1_REG;
		ctrl_reg = MPUREG_I2C_SLV1_CTRL;
		addr_trig_reg = 0;
		reg_trig_reg  = 0;
		ctrl_trig_reg = 0;
#if defined CONFIG_MPU_SENSORS_MPU6050B1
		bits_slave_delay = BIT_SLV1_DLY_EN;
#endif
		break;
	case EXT_SLAVE_TYPE_COMPASS:
		addr_reg = MPUREG_I2C_SLV0_ADDR;
		reg_reg  = MPUREG_I2C_SLV0_REG;
		ctrl_reg = MPUREG_I2C_SLV0_CTRL;
		addr_trig_reg = MPUREG_I2C_SLV2_ADDR;
		reg_trig_reg  = MPUREG_I2C_SLV2_REG;
		ctrl_trig_reg = MPUREG_I2C_SLV2_CTRL;
#if defined CONFIG_MPU_SENSORS_MPU6050B1
		d0_trig_reg   = MPUREG_I2C_SLV2_DO;
		bits_slave_delay = BIT_SLV2_DLY_EN | BIT_SLV0_DLY_EN;
#endif
		break;
	case EXT_SLAVE_TYPE_PRESSURE:
		addr_reg = MPUREG_I2C_SLV3_ADDR;
		reg_reg  = MPUREG_I2C_SLV3_REG;
		ctrl_reg = MPUREG_I2C_SLV3_CTRL;
		addr_trig_reg = MPUREG_I2C_SLV4_ADDR;
		reg_trig_reg  = MPUREG_I2C_SLV4_REG;
		ctrl_trig_reg = MPUREG_I2C_SLV4_CTRL;
#if defined CONFIG_MPU_SENSORS_MPU6050B1
		bits_slave_delay = BIT_SLV4_DLY_EN | BIT_SLV3_DLY_EN;
#endif
		break;
	default:
		LOG_RESULT_LOCATION(INV_ERROR_INVALID_PARAMETER);
		return INV_ERROR_INVALID_PARAMETER;
	};

	/* return if this slave has already been set */
	if ((slave_address &&
	     ((mldl_cfg->inv_mpu_state->i2c_slaves_enabled & bits_slave_delay)
		    == bits_slave_delay)) ||
	    (!slave_address &&
	     (mldl_cfg->inv_mpu_state->i2c_slaves_enabled & bits_slave_delay) ==
		    0))
		return 0;

	result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, true);

	/* Address */
	result = inv_serial_single_write(gyro_handle,
					 mldl_cfg->mpu_chip_info->addr,
					 addr_reg, slave_address);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	/* Register */
	result = inv_serial_single_write(gyro_handle,
					 mldl_cfg->mpu_chip_info->addr,
					 reg_reg, slave_reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	/* Length, byte swapping, grouping & enable */
	if (slave_len > BITS_SLV_LENG) {
		MPL_LOGW("Limiting slave burst read length to "
			 "the allowed maximum (15B, req. %d)\n", slave_len);
		slave_len = BITS_SLV_LENG;
		return INV_ERROR_INVALID_CONFIGURATION;
	}
	reg = slave_len;
	if (slave_endian == EXT_SLAVE_LITTLE_ENDIAN) {
		reg |= BIT_SLV_BYTE_SW;
		if (slave_reg & 1)
			reg |= BIT_SLV_GRP;
	}
	if (slave_address)
		reg |= BIT_SLV_ENABLE;

	result = inv_serial_single_write(gyro_handle,
					 mldl_cfg->mpu_chip_info->addr,
					 ctrl_reg, reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

#if defined CONFIG_MPU_SENSORS_MPU6050B1
	/* Trigger */
	if (addr_trig_reg) {
		/* If slave address is 0 this clears the trigger */
		result = inv_serial_single_write(gyro_handle,
						 mldl_cfg->mpu_chip_info->addr,
						 addr_trig_reg,
						 slave_address & ~BIT_I2C_READ);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	if (slave && slave->trigger && reg_trig_reg) {
		result = inv_serial_single_write(gyro_handle,
						 mldl_cfg->mpu_chip_info->addr,
						 reg_trig_reg,
						 slave->trigger->reg);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		result = inv_serial_single_write(gyro_handle,
						 mldl_cfg->mpu_chip_info->addr,
						 ctrl_trig_reg,
						 BIT_SLV_ENABLE | 0x01);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		result = inv_serial_single_write(gyro_handle,
						 mldl_cfg->mpu_chip_info->addr,
						 d0_trig_reg,
						 slave->trigger->value);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	} else if (ctrl_trig_reg) {
		result = inv_serial_single_write(gyro_handle,
						 mldl_cfg->mpu_chip_info->addr,
						 ctrl_trig_reg, 0x00);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	/* Data rate */
	if (slave) {
		struct ext_slave_config config;
		long data;
		config.key = MPU_SLAVE_CONFIG_ODR_RESUME;
		config.len = sizeof(long);
		config.apply = false;
		config.data = &data;
		if (!(slave->get_config))
			return INV_ERROR_INVALID_CONFIGURATION;

		result = slave->get_config(NULL, slave, slave_pdata, &config);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		MPL_LOGI("Slave %d ODR: %ld Hz\n", slave_id, data / 1000);
		divider = ((1000 * inv_mpu_get_sampling_rate_hz(
				    mldl_cfg->mpu_gyro_cfg))
			/ data) - 1;
	} else {
		divider = 0;
	}

	result = inv_serial_read(gyro_handle,
				mldl_cfg->mpu_chip_info->addr,
				MPUREG_I2C_MST_DELAY_CTRL,
				1, &delay_ctrl_orig);
	delay_ctrl = delay_ctrl_orig;
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	if (divider > 0 && divider <= MASK_I2C_MST_DLY) {
		result = inv_serial_read(gyro_handle,
					 mldl_cfg->mpu_chip_info->addr,
					 MPUREG_I2C_SLV4_CTRL, 1, &reg);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		if ((reg & MASK_I2C_MST_DLY) &&
			((long)(reg & MASK_I2C_MST_DLY) !=
				(divider & MASK_I2C_MST_DLY))) {
			MPL_LOGW("Changing slave divider: %ld to %ld\n",
				 (long)(reg & MASK_I2C_MST_DLY),
				 (divider & MASK_I2C_MST_DLY));

		}
		reg |= (unsigned char)(divider & MASK_I2C_MST_DLY);
		result = inv_serial_single_write(gyro_handle,
						 mldl_cfg->mpu_chip_info->addr,
						 MPUREG_I2C_SLV4_CTRL,
						 reg);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}

		delay_ctrl |= bits_slave_delay;
	} else {
		delay_ctrl &= ~(bits_slave_delay);
	}
	if (delay_ctrl != delay_ctrl_orig) {
		result = inv_serial_single_write(
			gyro_handle, mldl_cfg->mpu_chip_info->addr,
			MPUREG_I2C_MST_DELAY_CTRL,
			delay_ctrl);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}
#endif

	if (slave_address)
		mldl_cfg->inv_mpu_state->i2c_slaves_enabled |=
			bits_slave_delay;
	else
		mldl_cfg->inv_mpu_state->i2c_slaves_enabled &=
			~bits_slave_delay;

	return result;
}
#endif

static int mpu_set_slave(struct mldl_cfg *mldl_cfg,
			 void *gyro_handle,
			 struct ext_slave_descr *slave,
			 struct ext_slave_platform_data *slave_pdata,
			 int slave_id)
{
#if defined CONFIG_MPU_SENSORS_MPU3050
	return mpu_set_slave_mpu3050(mldl_cfg, gyro_handle, slave,
				     slave_pdata, slave_id);
#endif
#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
	return mpu_set_slave_mpu60xx(mldl_cfg, gyro_handle, slave,
				     slave_pdata, slave_id);
#endif
}
/**
 * Check to see if the gyro was reset by testing a couple of registers known
 * to change on reset.
 *
 * @mldl_cfg mldl configuration structure
 * @gyro_handle handle used to communicate with the gyro
 *
 * @return INV_SUCCESS or non-zero error code
 */
static int mpu_was_reset(struct mldl_cfg *mldl_cfg, void *gyro_handle)
{
	int result = INV_SUCCESS;
	unsigned char reg;

	result = inv_serial_read(gyro_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_DMP_CFG_2, 1, &reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	if (mldl_cfg->mpu_gyro_cfg->dmp_cfg2 != reg)
		return true;

	if (0 != mldl_cfg->mpu_gyro_cfg->dmp_cfg1)
		return false;

	result = inv_serial_read(gyro_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_SMPLRT_DIV, 1, &reg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	if (reg != mldl_cfg->mpu_gyro_cfg->divider)
		return true;

	if (0 != mldl_cfg->mpu_gyro_cfg->divider)
		return false;

	/* Inconclusive assume it was reset */
	return true;
}


int inv_mpu_set_firmware(struct mldl_cfg *mldl_cfg, void *mlsl_handle,
			 const unsigned char *data, int size)
{
	int bank, offset, write_size;
	int result;
	unsigned char read[MPU_MEM_BANK_SIZE];

	if (mldl_cfg->inv_mpu_state->status & MPU_DEVICE_IS_SUSPENDED) {
#if INV_CACHE_DMP == 1
		memcpy(mldl_cfg->mpu_ram->ram, data, size);
		return INV_SUCCESS;
#else
		LOG_RESULT_LOCATION(INV_ERROR_MEMORY_SET);
		return INV_ERROR_MEMORY_SET;
#endif
	}

	if (!(mldl_cfg->inv_mpu_state->status & MPU_DMP_IS_SUSPENDED)) {
		LOG_RESULT_LOCATION(INV_ERROR_MEMORY_SET);
		return INV_ERROR_MEMORY_SET;
        }
	/* Write and verify memory */
	for (bank = 0; size > 0; bank++,
			size -= write_size,
			data += write_size) {
		if (size > MPU_MEM_BANK_SIZE)
			write_size = MPU_MEM_BANK_SIZE;
		else
			write_size = size;

		result = inv_serial_write_mem(mlsl_handle,
				mldl_cfg->mpu_chip_info->addr,
				((bank << 8) | 0x00),
				write_size,
				data);
		if (result) {
			LOG_RESULT_LOCATION(result);
			MPL_LOGE("Write mem error in bank %d\n", bank);
			return result;
		}
		result = inv_serial_read_mem(mlsl_handle,
				mldl_cfg->mpu_chip_info->addr,
				((bank << 8) | 0x00),
				write_size,
				read);
		if (result) {
			LOG_RESULT_LOCATION(result);
			MPL_LOGE("Read mem error in bank %d\n", bank);
			return result;
		}

#if defined CONFIG_MPU_SENSORS_MPU6050A2 || \
	defined CONFIG_MPU_SENSORS_MPU6050B1
#define ML_SKIP_CHECK 38
#else
#define ML_SKIP_CHECK 20
#endif
		for (offset = 0; offset < write_size; offset++) {
			/* skip the register memory locations */
			if (bank == 0 && offset < ML_SKIP_CHECK)
				continue;
			if (data[offset] != read[offset]) {
				result = INV_ERROR_SERIAL_WRITE;
				break;
			}
		}
		if (result != INV_SUCCESS) {
			LOG_RESULT_LOCATION(result);
			MPL_LOGE("Read data mismatch at bank %d, offset %d\n",
				bank, offset);
			return result;
		}
	}
	return INV_SUCCESS;
}

static int gyro_resume(struct mldl_cfg *mldl_cfg, void *gyro_handle,
		       unsigned long sensors)
{
	int result;
	int ii;
	unsigned char reg;
	unsigned char regs[7];

	/* Wake up the part */
#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
	result = mpu60xx_pwr_mgmt(mldl_cfg, gyro_handle, false, sensors);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	if (!(mldl_cfg->inv_mpu_state->status & MPU_GYRO_NEEDS_CONFIG) &&
	    !mpu_was_reset(mldl_cfg, gyro_handle)) {
		return INV_SUCCESS;
	}

	/* Configure the MPU */
	result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 1);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_INT_ENABLE, (mldl_cfg->mpu_gyro_cfg->int_config));
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
#else
	result = mpu3050_pwr_mgmt(mldl_cfg, gyro_handle, false, false,
				  !(sensors & INV_X_GYRO),
				  !(sensors & INV_Y_GYRO),
				  !(sensors & INV_Z_GYRO));

	if (!(mldl_cfg->inv_mpu_state->status & MPU_GYRO_NEEDS_CONFIG) &&
	    !mpu_was_reset(mldl_cfg, gyro_handle)) {
		return INV_SUCCESS;
	}

	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_INT_CFG,
		(mldl_cfg->mpu_gyro_cfg->int_config |
			mldl_cfg->pdata->int_config));
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
#endif
	result = mpu_set_clock_source(gyro_handle, mldl_cfg);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_SMPLRT_DIV, mldl_cfg->mpu_gyro_cfg->divider);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
	reg = MPUREG_GYRO_CONFIG_VALUE(0, 0, 0,
				       mldl_cfg->mpu_gyro_cfg->full_scale);
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_GYRO_CONFIG, reg);
	reg = MPUREG_CONFIG_VALUE(mldl_cfg->mpu_gyro_cfg->ext_sync,
				  mldl_cfg->mpu_gyro_cfg->lpf);
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_CONFIG, reg);
#else
	reg = DLPF_FS_SYNC_VALUE(mldl_cfg->mpu_gyro_cfg->ext_sync,
				 mldl_cfg->mpu_gyro_cfg->full_scale,
				 mldl_cfg->mpu_gyro_cfg->lpf);
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_DLPF_FS_SYNC, reg);
#endif
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_DMP_CFG_1, mldl_cfg->mpu_gyro_cfg->dmp_cfg1);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_DMP_CFG_2, mldl_cfg->mpu_gyro_cfg->dmp_cfg2);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	/* Write and verify memory */
#if INV_CACHE_DMP != 0
	inv_mpu_set_firmware(mldl_cfg, gyro_handle,
		mldl_cfg->mpu_ram->ram, mldl_cfg->mpu_ram->length);
#endif

#ifdef CONFIG_MPU_SENSORS_MPU3050
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_XG_OFFS_TC, mldl_cfg->mpu_offsets->tc[0]);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_YG_OFFS_TC, mldl_cfg->mpu_offsets->tc[1]);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_ZG_OFFS_TC, mldl_cfg->mpu_offsets->tc[2]);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
#else
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_XG_OFFS_TC,
		((mldl_cfg->mpu_offsets->tc[0] << 1) & BITS_XG_OFFS_TC));
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	regs[0] = ((mldl_cfg->mpu_offsets->tc[1] << 1) & BITS_YG_OFFS_TC);
#ifdef CONFIG_MPU_SENSORS_MPU6050B1
	if (mldl_cfg->pdata->level_shifter)
		regs[0] |= BIT_I2C_MST_VDDIO;
#endif
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_YG_OFFS_TC, regs[0]);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_single_write(
		gyro_handle, mldl_cfg->mpu_chip_info->addr,
		MPUREG_ZG_OFFS_TC,
		((mldl_cfg->mpu_offsets->tc[2] << 1) & BITS_ZG_OFFS_TC));
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
#endif
	regs[0] = MPUREG_X_OFFS_USRH;
	for (ii = 0; ii < ARRAY_SIZE(mldl_cfg->mpu_offsets->gyro); ii++) {
		regs[1 + ii * 2] =
			(unsigned char)(mldl_cfg->mpu_offsets->gyro[ii] >> 8)
			& 0xff;
		regs[1 + ii * 2 + 1] =
			(unsigned char)(mldl_cfg->mpu_offsets->gyro[ii] & 0xff);
	}
	result = inv_serial_write(gyro_handle, mldl_cfg->mpu_chip_info->addr,
				  7, regs);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	/* Configure slaves */
	result = inv_mpu_set_level_shifter_bit(mldl_cfg, gyro_handle,
					       mldl_cfg->pdata->level_shifter);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_NEEDS_CONFIG;

	return result;
}

int gyro_config(void *mlsl_handle,
		struct mldl_cfg *mldl_cfg,
		struct ext_slave_config *data)
{
	struct mpu_gyro_cfg *mpu_gyro_cfg = mldl_cfg->mpu_gyro_cfg;
	struct mpu_chip_info *mpu_chip_info = mldl_cfg->mpu_chip_info;
	struct mpu_offsets *mpu_offsets = mldl_cfg->mpu_offsets;
	int ii;

	if (!data->data)
		return INV_ERROR_INVALID_PARAMETER;

	switch (data->key) {
	case MPU_SLAVE_INT_CONFIG:
		mpu_gyro_cfg->int_config = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_EXT_SYNC:
		mpu_gyro_cfg->ext_sync = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_FULL_SCALE:
		mpu_gyro_cfg->full_scale = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_LPF:
		mpu_gyro_cfg->lpf = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_CLK_SRC:
		mpu_gyro_cfg->clk_src = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_DIVIDER:
		mpu_gyro_cfg->divider = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_DMP_ENABLE:
		mpu_gyro_cfg->dmp_enable = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_FIFO_ENABLE:
		mpu_gyro_cfg->fifo_enable = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_DMP_CFG1:
		mpu_gyro_cfg->dmp_cfg1 = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_DMP_CFG2:
		mpu_gyro_cfg->dmp_cfg2 = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_TC:
		for (ii = 0; ii < GYRO_NUM_AXES; ii++)
			mpu_offsets->tc[ii] = ((unsigned char *)data->data)[ii];
		break;
	case MPU_SLAVE_GYRO:
		for (ii = 0; ii < GYRO_NUM_AXES; ii++)
			mpu_offsets->gyro[ii] = ((unsigned short *)data->data)[ii];
		break;
	case MPU_SLAVE_ADDR:
		mpu_chip_info->addr = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_PRODUCT_REVISION:
		mpu_chip_info->product_revision = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_SILICON_REVISION:
		mpu_chip_info->silicon_revision = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_PRODUCT_ID:
		mpu_chip_info->product_id = *((unsigned char *)data->data);
		break;
	case MPU_SLAVE_GYRO_SENS_TRIM:
		mpu_chip_info->gyro_sens_trim = *((unsigned short *)data->data);
		break;
	case MPU_SLAVE_ACCEL_SENS_TRIM:
		mpu_chip_info->accel_sens_trim = *((unsigned short *)data->data);
		break;
	case MPU_SLAVE_RAM:
		if (data->len != mldl_cfg->mpu_ram->length)
			return INV_ERROR_INVALID_PARAMETER;

		memcpy(mldl_cfg->mpu_ram->ram, data->data, data->len);
		break;
	default:
		LOG_RESULT_LOCATION(INV_ERROR_FEATURE_NOT_IMPLEMENTED);
		return INV_ERROR_FEATURE_NOT_IMPLEMENTED;
	};
	mldl_cfg->inv_mpu_state->status |= MPU_GYRO_NEEDS_CONFIG;
	return INV_SUCCESS;
}

int gyro_get_config(void *mlsl_handle,
		struct mldl_cfg *mldl_cfg,
		struct ext_slave_config *data)
{
	struct mpu_gyro_cfg *mpu_gyro_cfg = mldl_cfg->mpu_gyro_cfg;
	struct mpu_chip_info *mpu_chip_info = mldl_cfg->mpu_chip_info;
	struct mpu_offsets *mpu_offsets = mldl_cfg->mpu_offsets;
	int ii;

	if (!data->data)
		return INV_ERROR_INVALID_PARAMETER;

	switch (data->key) {
	case MPU_SLAVE_INT_CONFIG:
		*((unsigned char *)data->data) = mpu_gyro_cfg->int_config;
		break;
	case MPU_SLAVE_EXT_SYNC:
		*((unsigned char *)data->data) = mpu_gyro_cfg->ext_sync;
		break;
	case MPU_SLAVE_FULL_SCALE:
		*((unsigned char *)data->data) = mpu_gyro_cfg->full_scale;
		break;
	case MPU_SLAVE_LPF:
		*((unsigned char *)data->data) = mpu_gyro_cfg->lpf;
		break;
	case MPU_SLAVE_CLK_SRC:
		*((unsigned char *)data->data) = mpu_gyro_cfg->clk_src;
		break;
	case MPU_SLAVE_DIVIDER:
		*((unsigned char *)data->data) = mpu_gyro_cfg->divider;
		break;
	case MPU_SLAVE_DMP_ENABLE:
		*((unsigned char *)data->data) = mpu_gyro_cfg->dmp_enable;
		break;
	case MPU_SLAVE_FIFO_ENABLE:
		*((unsigned char *)data->data) = mpu_gyro_cfg->fifo_enable;
		break;
	case MPU_SLAVE_DMP_CFG1:
		*((unsigned char *)data->data) = mpu_gyro_cfg->dmp_cfg1;
		break;
	case MPU_SLAVE_DMP_CFG2:
		*((unsigned char *)data->data) = mpu_gyro_cfg->dmp_cfg2;
		break;
	case MPU_SLAVE_TC:
		for (ii = 0; ii < GYRO_NUM_AXES; ii++)
			((unsigned char *)data->data)[ii] = mpu_offsets->tc[ii];
		break;
	case MPU_SLAVE_GYRO:
		for (ii = 0; ii < GYRO_NUM_AXES; ii++)
			((unsigned short *)data->data)[ii] = mpu_offsets->gyro[ii];
		break;
	case MPU_SLAVE_ADDR:
		*((unsigned char *)data->data) = mpu_chip_info->addr;
		break;
	case MPU_SLAVE_PRODUCT_REVISION:
		*((unsigned char *)data->data) = mpu_chip_info->product_revision;
		break;
	case MPU_SLAVE_SILICON_REVISION:
		*((unsigned char *)data->data) = mpu_chip_info->silicon_revision;
		break;
	case MPU_SLAVE_PRODUCT_ID:
		*((unsigned char *)data->data) = mpu_chip_info->product_id;
		break;
	case MPU_SLAVE_GYRO_SENS_TRIM:
		*((unsigned short *)data->data) = mpu_chip_info->gyro_sens_trim;
		break;
	case MPU_SLAVE_ACCEL_SENS_TRIM:
		*((unsigned short *)data->data) = mpu_chip_info->accel_sens_trim;
		break;
	case MPU_SLAVE_RAM:
		if (data->len != mldl_cfg->mpu_ram->length)
			return INV_ERROR_INVALID_PARAMETER;

		memcpy(data->data, mldl_cfg->mpu_ram->ram, data->len);
		break;
	default:
		LOG_RESULT_LOCATION(INV_ERROR_FEATURE_NOT_IMPLEMENTED);
		return INV_ERROR_FEATURE_NOT_IMPLEMENTED;
	};

	return INV_SUCCESS;
}


/*******************************************************************************
 *******************************************************************************
 * Exported functions
 *******************************************************************************
 ******************************************************************************/

/**
 * Initializes the pdata structure to defaults.
 *
 * Opens the device to read silicon revision, product id and whoami.
 *
 * @mldl_cfg
 *          The internal device configuration data structure.
 * @mlsl_handle
 *          The serial communication handle.
 *
 * @return INV_SUCCESS if silicon revision, product id and woami are supported
 *         by this software.
 */
int inv_mpu_open(struct mldl_cfg *mldl_cfg,
		 void *mlsl_handle,
		 void *accel_handle,
		 void *compass_handle, void *pressure_handle)
{
	int result;
	int ii;

	/* Default is Logic HIGH, pushpull, latch disabled, anyread to clear */
	mldl_cfg->inv_mpu_cfg->ignore_system_suspend = false;
	mldl_cfg->mpu_gyro_cfg->int_config = BIT_DMP_INT_EN;
	mldl_cfg->mpu_gyro_cfg->clk_src = MPU_CLK_SEL_PLLGYROZ;
	mldl_cfg->mpu_gyro_cfg->lpf = MPU_FILTER_42HZ;
	mldl_cfg->mpu_gyro_cfg->full_scale = MPU_FS_2000DPS;
	mldl_cfg->mpu_gyro_cfg->divider = 4;
	mldl_cfg->mpu_gyro_cfg->dmp_enable = 1;
	mldl_cfg->mpu_gyro_cfg->fifo_enable = 1;
	mldl_cfg->mpu_gyro_cfg->ext_sync = 0;
	mldl_cfg->mpu_gyro_cfg->dmp_cfg1 = 0;
	mldl_cfg->mpu_gyro_cfg->dmp_cfg2 = 0;
	mldl_cfg->inv_mpu_state->status =
		MPU_DMP_IS_SUSPENDED |
		MPU_GYRO_IS_SUSPENDED |
		MPU_ACCEL_IS_SUSPENDED |
		MPU_COMPASS_IS_SUSPENDED |
		MPU_PRESSURE_IS_SUSPENDED |
		MPU_DEVICE_IS_SUSPENDED;
	mldl_cfg->inv_mpu_state->i2c_slaves_enabled = 0;

	if (mldl_cfg->mpu_chip_info->addr == 0) {
		LOG_RESULT_LOCATION(INV_ERROR_INVALID_PARAMETER);
		return INV_ERROR_INVALID_PARAMETER;
	}

	/*
	 * Reset,
	 * Take the DMP out of sleep, and
	 * read the product_id, sillicon rev and whoami
	 */
#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
	mldl_cfg->inv_mpu_state->status &= ~MPU_GYRO_IS_BYPASSED;
	result = mpu60xx_pwr_mgmt(mldl_cfg, mlsl_handle, true,
				  INV_THREE_AXIS_GYRO);
#else
	mldl_cfg->inv_mpu_state->status |= MPU_GYRO_IS_BYPASSED;
	result = mpu3050_pwr_mgmt(mldl_cfg, mlsl_handle, RESET, 0, 0, 0, 0);
#endif
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	result = inv_get_silicon_rev(mldl_cfg, mlsl_handle);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	/* Get the factory temperature compensation offsets */
	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_XG_OFFS_TC, 1,
				 &mldl_cfg->mpu_offsets->tc[0]);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_YG_OFFS_TC, 1,
				 &mldl_cfg->mpu_offsets->tc[1]);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}
	result = inv_serial_read(mlsl_handle, mldl_cfg->mpu_chip_info->addr,
				 MPUREG_ZG_OFFS_TC, 1,
				 &mldl_cfg->mpu_offsets->tc[2]);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	/* Into bypass mode before sleeping and calling the slaves init */
	result = mpu_set_i2c_bypass(mldl_cfg, mlsl_handle, true);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
	for (ii = 0; ii < GYRO_NUM_AXES; ii++) {
		mldl_cfg->mpu_offsets->tc[ii] =
		    (mldl_cfg->mpu_offsets->tc[ii] & BITS_XG_OFFS_TC) >> 1;
	}
#endif

#if INV_CACHE_DMP != 0
#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
	result = mpu60xx_pwr_mgmt(mldl_cfg, mlsl_handle, false, 0);
#else
	result = mpu3050_pwr_mgmt(mldl_cfg, mlsl_handle, 0, SLEEP, 0, 0, 0);
#endif
#endif
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	for (ii = 0; ii < EXT_SLAVE_NUM_TYPES; ii++) {

		if (!mldl_cfg->slave[ii] || !mldl_cfg->slave[ii]->init)
			continue;

		result = mldl_cfg->slave[ii]->init(accel_handle,
						mldl_cfg->slave[ii],
						mldl_cfg->pdata_slave[ii]);
		if (result) {
			LOG_RESULT_LOCATION(result);
			goto out_slave_failure;
		}

	}

#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
	if (mldl_cfg->slave[EXT_SLAVE_TYPE_ACCEL] &&
		mldl_cfg->slave[EXT_SLAVE_TYPE_ACCEL]->id == ACCEL_ID_MPU6050) {
		/* pass a reference to the mldl_cfg data
		   structure to the mpu6050 accel "class" */
		struct ext_slave_config config;
		config.key = MPU_SLAVE_CONFIG_INTERNAL_REFERENCE;
		config.len = sizeof(struct mldl_cfg *);
		config.apply = true;
		config.data = mldl_cfg;
		result = mldl_cfg->slave[EXT_SLAVE_TYPE_ACCEL]->config(
			accel_handle,
			mldl_cfg->slave[EXT_SLAVE_TYPE_ACCEL],
			mldl_cfg->pdata_slave[EXT_SLAVE_TYPE_ACCEL],
			&config);
		if (result) {
			LOG_RESULT_LOCATION(result);
			goto out_slave_failure;
		}
	}
#endif

	return result;

out_slave_failure:
	for (ii = ii - 1; ii >= 0; ii--)
		if (mldl_cfg->slave[ii] && mldl_cfg->slave[ii]->exit)
			mldl_cfg->slave[ii]->exit(compass_handle,
						mldl_cfg->slave[ii],
						mldl_cfg->pdata_slave[ii]);
	return result;
}

/**
 * Close the mpu interface
 *
 * @mldl_cfg pointer to the configuration structure
 * @mlsl_handle pointer to the serial layer handle
 *
 * @return INV_SUCCESS or non-zero error code
 */
int inv_mpu_close(struct mldl_cfg *mldl_cfg,
		  void *mlsl_handle,
		  void *accel_handle,
		  void *compass_handle,
		  void *pressure_handle)
{
	int result = INV_SUCCESS;
	int ret_result = INV_SUCCESS;
	int ii;

	for (ii = 0; ii < EXT_SLAVE_NUM_TYPES; ii++) {
		if (!mldl_cfg->slave[ii] || !mldl_cfg->slave[ii]->exit)
			continue;
		result = mldl_cfg->slave[ii]->exit(accel_handle,
						mldl_cfg->slave[ii],
						mldl_cfg->pdata_slave[ii]);
		if (INV_SUCCESS != result)
			MPL_LOGE("Slave %d exit failed %d\n", ii, result);

		if (INV_SUCCESS == ret_result)
			ret_result = result;
	}

	return ret_result;
}

/**
 *  @brief  resume the MPU device and all the other sensor
 *          devices from their low power state.
 *
 *  @mldl_cfg
 *              pointer to the configuration structure
 *  @gyro_handle
 *              the main file handle to the MPU device.
 *  @accel_handle
 *              an handle to the accelerometer device, if sitting
 *              onto a separate bus. Can match mlsl_handle if
 *              the accelerometer device operates on the same
 *              primary bus of MPU.
 *  @compass_handle
 *              an handle to the compass device, if sitting
 *              onto a separate bus. Can match mlsl_handle if
 *              the compass device operates on the same
 *              primary bus of MPU.
 *  @pressure_handle
 *              an handle to the pressure sensor device, if sitting
 *              onto a separate bus. Can match mlsl_handle if
 *              the pressure sensor device operates on the same
 *              primary bus of MPU.
 *  @resume_gyro
 *              whether resuming the gyroscope device is
 *              actually needed (if the device supports low power
 *              mode of some sort).
 *  @resume_accel
 *              whether resuming the accelerometer device is
 *              actually needed (if the device supports low power
 *              mode of some sort).
 *  @resume_compass
 *              whether resuming the compass device is
 *              actually needed (if the device supports low power
 *              mode of some sort).
 *  @resume_pressure
 *              whether resuming the pressure sensor device is
 *              actually needed (if the device supports low power
 *              mode of some sort).
 *  @return  INV_SUCCESS or a non-zero error code.
 */
int inv_mpu_resume(struct mldl_cfg *mldl_cfg,
		   void *gyro_handle,
		   void *accel_handle,
		   void *compass_handle,
		   void *pressure_handle,
		   unsigned long sensors)
{
	int result = INV_SUCCESS;
	int ii;
	bool resume_slave[EXT_SLAVE_NUM_TYPES];
	bool resume_dmp = sensors & INV_DMP_PROCESSOR;
	void *slave_handle[EXT_SLAVE_NUM_TYPES];
	resume_slave[EXT_SLAVE_TYPE_GYROSCOPE] =
		(sensors & (INV_X_GYRO | INV_Y_GYRO | INV_Z_GYRO));
	resume_slave[EXT_SLAVE_TYPE_ACCEL] =
		sensors & INV_THREE_AXIS_ACCEL;
	resume_slave[EXT_SLAVE_TYPE_COMPASS] =
		sensors & INV_THREE_AXIS_COMPASS;
	resume_slave[EXT_SLAVE_TYPE_PRESSURE] =
		sensors & INV_THREE_AXIS_PRESSURE;

	slave_handle[EXT_SLAVE_TYPE_GYROSCOPE] = gyro_handle;
	slave_handle[EXT_SLAVE_TYPE_ACCEL] = accel_handle;
	slave_handle[EXT_SLAVE_TYPE_COMPASS] = compass_handle;
	slave_handle[EXT_SLAVE_TYPE_PRESSURE] = pressure_handle;


#ifndef UMPL
	mldl_print_cfg(mldl_cfg);
#endif
	
	/* Skip the Gyro since slave[EXT_SLAVE_TYPE_GYROSCOPE] is NULL */
	for (ii = EXT_SLAVE_TYPE_ACCEL; ii < EXT_SLAVE_NUM_TYPES; ii++) {
		if (resume_slave[ii] &&
		    ((!mldl_cfg->slave[ii]) ||
			(!mldl_cfg->slave[ii]->resume))) {
			LOG_RESULT_LOCATION(INV_ERROR_INVALID_PARAMETER);
			return INV_ERROR_INVALID_PARAMETER;
		}
	}

	if ((resume_slave[EXT_SLAVE_TYPE_GYROSCOPE] || resume_dmp)
	    && ((mldl_cfg->inv_mpu_state->status & MPU_GYRO_IS_SUSPENDED) ||
		(mldl_cfg->inv_mpu_state->status & MPU_GYRO_NEEDS_CONFIG))) {
		result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 1);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		result = dmp_stop(mldl_cfg, gyro_handle);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		result = gyro_resume(mldl_cfg, gyro_handle, sensors);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	for (ii = 0; ii < EXT_SLAVE_NUM_TYPES; ii++) {
		if (!mldl_cfg->slave[ii] ||
		    !mldl_cfg->pdata_slave[ii] ||
		    !resume_slave[ii] ||
		    !(mldl_cfg->inv_mpu_state->status & (1 << ii)))
			continue;

		if (EXT_SLAVE_BUS_SECONDARY ==
		    mldl_cfg->pdata_slave[ii]->bus) {
			result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle,
						    true);
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
		}
		result = mldl_cfg->slave[ii]->resume(slave_handle[ii],
						mldl_cfg->slave[ii],
						mldl_cfg->pdata_slave[ii]);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		mldl_cfg->inv_mpu_state->status &= ~(1 << ii);
	}

	for (ii = 0; ii < EXT_SLAVE_NUM_TYPES; ii++) {
		if (resume_dmp &&
		    !(mldl_cfg->inv_mpu_state->status & (1 << ii)) &&
		    mldl_cfg->pdata_slave[ii] &&
		    EXT_SLAVE_BUS_SECONDARY == mldl_cfg->pdata_slave[ii]->bus) {
			result = mpu_set_slave(mldl_cfg,
					gyro_handle,
					mldl_cfg->slave[ii],
					mldl_cfg->pdata_slave[ii],
					mldl_cfg->slave[ii]->type);
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
		}
	}

	/* Turn on the master i2c iterface if necessary */
	if (resume_dmp) {
		result = mpu_set_i2c_bypass(
			mldl_cfg, gyro_handle,
			!(mldl_cfg->inv_mpu_state->i2c_slaves_enabled));
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}

		/* Now start */
		result = dmp_start(mldl_cfg, gyro_handle);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}
	mldl_cfg->inv_mpu_cfg->requested_sensors = sensors;

	return result;
}

/**
 *  @brief  suspend the MPU device and all the other sensor
 *          devices into their low power state.
 *  @mldl_cfg
 *              a pointer to the struct mldl_cfg internal data
 *              structure.
 *  @gyro_handle
 *              the main file handle to the MPU device.
 *  @accel_handle
 *              an handle to the accelerometer device, if sitting
 *              onto a separate bus. Can match gyro_handle if
 *              the accelerometer device operates on the same
 *              primary bus of MPU.
 *  @compass_handle
 *              an handle to the compass device, if sitting
 *              onto a separate bus. Can match gyro_handle if
 *              the compass device operates on the same
 *              primary bus of MPU.
 *  @pressure_handle
 *              an handle to the pressure sensor device, if sitting
 *              onto a separate bus. Can match gyro_handle if
 *              the pressure sensor device operates on the same
 *              primary bus of MPU.
 *  @accel
 *              whether suspending the accelerometer device is
 *              actually needed (if the device supports low power
 *              mode of some sort).
 *  @compass
 *              whether suspending the compass device is
 *              actually needed (if the device supports low power
 *              mode of some sort).
 *  @pressure
 *              whether suspending the pressure sensor device is
 *              actually needed (if the device supports low power
 *              mode of some sort).
 *  @return  INV_SUCCESS or a non-zero error code.
 */
int inv_mpu_suspend(struct mldl_cfg *mldl_cfg,
		    void *gyro_handle,
		    void *accel_handle,
		    void *compass_handle,
		    void *pressure_handle,
		    unsigned long sensors)
{
	int result = INV_SUCCESS;
	int ii;
	struct ext_slave_descr **slave = mldl_cfg->slave;
	struct ext_slave_platform_data **pdata_slave = mldl_cfg->pdata_slave;
	bool suspend_dmp = ((sensors & INV_DMP_PROCESSOR) == INV_DMP_PROCESSOR);
	bool suspend_slave[EXT_SLAVE_NUM_TYPES];

	suspend_slave[EXT_SLAVE_TYPE_GYROSCOPE] =
		((sensors & (INV_X_GYRO | INV_Y_GYRO | INV_Z_GYRO))
			== (INV_X_GYRO | INV_Y_GYRO | INV_Z_GYRO));
	suspend_slave[EXT_SLAVE_TYPE_ACCEL] =
		((sensors & INV_THREE_AXIS_ACCEL) == INV_THREE_AXIS_ACCEL);
	suspend_slave[EXT_SLAVE_TYPE_COMPASS] =
		((sensors & INV_THREE_AXIS_COMPASS) == INV_THREE_AXIS_COMPASS);
	suspend_slave[EXT_SLAVE_TYPE_PRESSURE] =
		((sensors & INV_THREE_AXIS_PRESSURE) ==
			INV_THREE_AXIS_PRESSURE);

	if (suspend_dmp) {
		result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 1);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		result = dmp_stop(mldl_cfg, gyro_handle);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	/* Gyro */
	if (suspend_slave[EXT_SLAVE_TYPE_GYROSCOPE] &&
	    !(mldl_cfg->inv_mpu_state->status & MPU_GYRO_IS_SUSPENDED)) {
#if defined CONFIG_MPU_SENSORS_MPU6050A2 || defined CONFIG_MPU_SENSORS_MPU6050B1
		result = mpu60xx_pwr_mgmt(mldl_cfg, gyro_handle, false,
					((~sensors) & INV_ALL_SENSORS));
#else
		result = mpu3050_pwr_mgmt(
			mldl_cfg, gyro_handle, 0,
			suspend_dmp && suspend_slave[EXT_SLAVE_TYPE_GYROSCOPE],
			(unsigned char)(sensors & INV_X_GYRO),
			(unsigned char)(sensors & INV_Y_GYRO),
			(unsigned char)(sensors & INV_Z_GYRO));
#endif
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	for (ii = 0; ii < EXT_SLAVE_NUM_TYPES; ii++) {
		bool is_suspended = mldl_cfg->inv_mpu_state->status & (1 << ii);
		if (!slave[ii]   || !pdata_slave[ii] ||
		    is_suspended || !suspend_slave[ii])
			continue;

		if (EXT_SLAVE_BUS_SECONDARY == pdata_slave[ii]->bus) {
			result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 1);
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
		}
		result = slave[ii]->suspend(accel_handle,
						  slave[ii],
						  pdata_slave[ii]);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
		if (EXT_SLAVE_BUS_SECONDARY == pdata_slave[ii]->bus) {
			result = mpu_set_slave(mldl_cfg, gyro_handle,
					       NULL, NULL,
					       slave[ii]->type);
			if (result) {
				LOG_RESULT_LOCATION(result);
				return result;
			}
		}
		mldl_cfg->inv_mpu_state->status |= (1 << ii);
	}

	/* Re-enable the i2c master if there are configured slaves and DMP */
	if (!suspend_dmp) {
		result = mpu_set_i2c_bypass(
			mldl_cfg, gyro_handle,
			!(mldl_cfg->inv_mpu_state->i2c_slaves_enabled));
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}
	mldl_cfg->inv_mpu_cfg->requested_sensors = (~sensors) & INV_ALL_SENSORS;

	return result;
}

int inv_mpu_slave_read(struct mldl_cfg *mldl_cfg,
		       void *gyro_handle,
		       void *slave_handle,
		       struct ext_slave_descr *slave,
		       struct ext_slave_platform_data *pdata,
		       unsigned char *data)
{
	int result;
	int bypass_result;
	int remain_bypassed = true;

	if (NULL == slave || NULL == slave->read) {
		LOG_RESULT_LOCATION(INV_ERROR_INVALID_CONFIGURATION);
		return INV_ERROR_INVALID_CONFIGURATION;
	}

	if ((EXT_SLAVE_BUS_SECONDARY == pdata->bus)
	    && (!(mldl_cfg->inv_mpu_state->status & MPU_GYRO_IS_BYPASSED))) {
		remain_bypassed = false;
		result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 1);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	result = slave->read(slave_handle, slave, pdata, data);

	if (!remain_bypassed) {
		bypass_result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 0);
		if (bypass_result) {
			LOG_RESULT_LOCATION(bypass_result);
			return bypass_result;
		}
	}
	return result;
}

int inv_mpu_slave_config(struct mldl_cfg *mldl_cfg,
			 void *gyro_handle,
			 void *slave_handle,
			 struct ext_slave_config *data,
			 struct ext_slave_descr *slave,
			 struct ext_slave_platform_data *pdata)
{
	int result;
	int remain_bypassed = true;

	if (NULL == slave || NULL == slave->config) {
		LOG_RESULT_LOCATION(INV_ERROR_INVALID_CONFIGURATION);
		return INV_ERROR_INVALID_CONFIGURATION;
	}

	if (data->apply && (EXT_SLAVE_BUS_SECONDARY == pdata->bus)
	    && (!(mldl_cfg->inv_mpu_state->status & MPU_GYRO_IS_BYPASSED))) {
		remain_bypassed = false;
		result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 1);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	result = slave->config(slave_handle, slave, pdata, data);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	if (!remain_bypassed) {
		result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 0);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}
	return result;
}

int inv_mpu_get_slave_config(struct mldl_cfg *mldl_cfg,
			     void *gyro_handle,
			     void *slave_handle,
			     struct ext_slave_config *data,
			     struct ext_slave_descr *slave,
			     struct ext_slave_platform_data *pdata)
{
	int result;
	int remain_bypassed = true;

	if (NULL == slave || NULL == slave->get_config) {
		LOG_RESULT_LOCATION(INV_ERROR_INVALID_CONFIGURATION);
		return INV_ERROR_INVALID_CONFIGURATION;
	}

	if (data->apply && (EXT_SLAVE_BUS_SECONDARY == pdata->bus)
	    && (!(mldl_cfg->inv_mpu_state->status & MPU_GYRO_IS_BYPASSED))) {
		remain_bypassed = false;
		result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 1);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}

	result = slave->get_config(slave_handle, slave, pdata, data);
	if (result) {
		LOG_RESULT_LOCATION(result);
		return result;
	}

	if (!remain_bypassed) {
		result = mpu_set_i2c_bypass(mldl_cfg, gyro_handle, 0);
		if (result) {
			LOG_RESULT_LOCATION(result);
			return result;
		}
	}
	return result;
}

/**
 * @}
 */
