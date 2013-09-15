/*
 * Copyright � 2007-2010 Microchip Technology Inc.  All rights reserved.
 *
 *
 * You may use this software, and any derivatives, exclusively with Microchip�s products. 
 * Microchip and its licensors retain all ownership and intellectual property rights in 
 * the accompanying software and in all derivatives hereto.  This software and any 
 * accompanying information is for suggestion only.  It does not modify Microchip�s 
 * standard warranty for its products.  You agree that you are solely responsible for 
 * testing the software and determining its suitability.  Microchip has no obligation 
 * to modify, test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, 
 * IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE, ITS 
 * INTERACTION WITH MICROCHIP�S PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN 
 * ANY APPLICATION. 
 *
 * IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT 
 * (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, 
 * CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL 
 * OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO 
 * THE SOFTWARE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY 
 * OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S 
 * TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE 
 * AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS.
 */


/*
 $License:
    Copyright (C) 2010 InvenSense Corporation, All Rights Reserved.
 $
 */

/******************************************************************************
 * $Id: mlsl_linux.c 4639 2011-01-28 04:39:15Z yserlin $
 *****************************************************************************/

/** 
 *  @defgroup MLSL (Motion Library - Serial Layer)
 *  @brief  The Motion Library System Layer provides the Motion Library the 
 *          interface to the system functions.
 *
 *  @{
 *      @file   mlsl_at32.c
 *      @brief  The Motion Library System Layer.
 *
 */


/* ------------------ */
/* - Include Files. - */
/* ------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <plib.h>
//#include <i2c.h>

#include "log.h"
//#undef MPL_LOG_TAG
//#define MPL_LOG_TAG "mlsl-at32"

//#define DEBUGI2C

#include "mpu.h"

#include "../i2c_mpu.h"

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
#include "mlinclude.h"
#include "stdint_invensense.h"

//#include "twim.h"
#include "umplCalClient.h"

/*//
// Wrap around a new plib
//
#define I2C2StartCondition() I2CStart(I2C2)
//#define I2C2ByteWrite ( I2CSendByte(I2C2,

int I2C2ByteWrite(BYTE data) {
  I2CSendByte(I2C2, data);  
}

int MultiByteWriteI2C2(const unsigned char* data, int length) {
    //writeStatus = MultiByteWriteI2C2(data, length);		// do all data in array
    int x;
    char buffer[8];
    //for(x = 0; x < strlen(data)/8; x++) {
    for(x = 0; x < length/8; x++) {
        memcpy(buffer, &data[x*8], 8);
        I2CSendByte(I2C2, buffer);
    }

    return 0;
}*/

#ifdef DEBUG
#define _SerialError(...) MPL_LOGE(__VA_ARGS__)
#define _SerialDebug(...) MPL_LOGD(__VA_ARGS__)
#else
#define _SerialError(...) do {} while(0)
#define _SerialDebug(...) do {} while(0)
#endif

/**
 * @brief stub on at32 platform. The Atmel ASF twim library,
 *        which provides twim_read and twim_write,
 *        should be configured before this is called.
 *
 * @param port  Unused, pass as NULL
 * @param sl_handle  Unused, pass as NULL
 */

inv_error_t inv_serial_open(char const * port, void **sl_handle)
{
    return INV_SUCCESS;
}

inv_error_t inv_serial_reset(void *sl_handle)
{
    return INV_SUCCESS;
}

inv_error_t inv_serial_close(void *sl_handle)
{
    return INV_SUCCESS;
}

/**
 *  @brief  used as generic serial write. Does not accept a
 *          register parameter like the rest of the MLSLSerial
 *          functions - if used to write to a register, the register
 *          address should be the first member of data
 *          This should be sent by I2C.
 *
 *  @param  sl_handle       Unused, pass as NULL
 *  @param  slaveAddr       I2C slave address of device.
 *  @param  length          Length of burst of data.
 *  @param  data            Pointer to block of data.
 *
 *  @return INV_SUCCESS if successful, a non-zero error code otherwise.
 */
inv_error_t inv_serial_write( void *sl_handle,
						  unsigned char slaveAddr,
                          unsigned short length,
                          unsigned char const *data )
{
    int regAddr;
	int writeStatus;

	//MPL_LOGV("Doing inv_serial_write\n");
	
	regAddr = data[0];	// starting register address is first byte of data.
	slaveAddr = slaveAddr << 1;		// shift address to the left by one bit.
	
	data = data + 1;    	//  advance pointer so that I skip the address.

	if(!I2C2StartCondition()) return(FAIL);					// Start condition
		if(!I2C2ByteWrite(slaveAddr)) return(FAIL);			// I2C address
		if(!I2C2ByteWrite(regAddr)) return(FAIL);			// internal register address

		IdleI2C2();					// wait for bus idle condition

		writeStatus = MultiByteWriteI2C2(data, length);		// do all data in array

		I2C2StopWithDelay();											// Stop condition
		IdleI2C2();							// Wait for Idle condition before I exit.

    return INV_SUCCESS;
}



/**
 *  @brief  used to write a single byte to a single register.
 *
 *  @param  sl_handle       Unused, pass as NULL
 *  @param  slaveAddr       I2C slave address of device.
 *  @param  registerAddr    Register address to write.
 *  @param  data            Single byte of data to write.
 *
 *  @return INV_SUCCESS if successful, a non-zero error code otherwise.
 */
inv_error_t inv_serial_single_write(void *sl_handle,
                                    unsigned char slaveAddr, 
                                    unsigned char registerAddr, 
                                    unsigned char data)
{
    unsigned char tempData[1];
	tempData[0] = data;
	unsigned short delayCount;
	slaveAddr = slaveAddr << 1;		// shift address to the left by one bit.

	//MPL_LOGV("doing inv_serial_single_write\n");

	if(!I2C2StartCondition()) return(FAIL);					// Start condition
	if(!I2C2ByteWrite(slaveAddr)) return(FAIL);				// I2C address
	if(!I2C2ByteWrite(registerAddr)) return(FAIL);			// internal register address
	if(!I2C2ByteWrite(data)) return(FAIL);					// and the data

	I2C2StopWithDelay();												// Stop Condition							
    
    return INV_SUCCESS;
}


/**
 *  @brief  used to write multiple bytes of data to DMP memory.
 *
 *  @param  sl_handle       Unused, pass as NULL
 *  @param  slaveAddr       I2C slave address of device.
 *  @param  memAddr         The location in the memory to write to. 16 bits.
 *  @param  length          Length of burst data. Must not cross 8-bit address boundary.
 *  @param  data            Pointer to block of data.
 *
 *  @return Zero if successful; an error code otherwise
 */
inv_error_t inv_serial_write_mem( void *sl_handle,
							 unsigned char slaveAddr,
                             unsigned short memAddr,
                             unsigned short length, 
                             unsigned char const *data )
{
     inv_error_t result;
	unsigned char tmpAddr;
	unsigned char bankAddr, regAddr;
	unsigned short bytesWritten = 0;
	int i;

		//MPL_LOGV("doing inv_serial_write_mem\n");

	/* Write bank - first time only */

	slaveAddr = slaveAddr << 1;		// shift address to the left by one bit.

    tmpAddr = MPUREG_BANK_SEL;
	regAddr = memAddr & 0xff;
    bankAddr = memAddr >> 8;

	//  Set memory bank

			if(!I2C2StartCondition()) return(FAIL);				// Start condition
			if(!I2C2ByteWrite(slaveAddr)) return(FAIL);			// I2C address - write
			if(!I2C2ByteWrite(tmpAddr)) return(FAIL);			// internal register address
			if(!I2C2ByteWrite(bankAddr)) return(FAIL);			// and write the data
			I2C2StopWithDelay();											// Stop condition to end recepti

	//  Set memory location

	while(bytesWritten < length)
	{
		unsigned short thisLen = min(SERIAL_MAX_TRANSFER_SIZE, length-bytesWritten);
		
		tmpAddr = MPUREG_MEM_START_ADDR;
		regAddr = regAddr + bytesWritten;

		if(!I2C2StartCondition()) return(FAIL);				// Start condition
		if(!I2C2ByteWrite(slaveAddr)) return(FAIL);			// I2C address - write
		if(!I2C2ByteWrite(tmpAddr)) return(FAIL);			// internal register address
		if(!I2C2ByteWrite(regAddr)) return(FAIL);		// and write the data
		I2C2StopWithDelay();											// Stop condition to end reception


		if(!I2C2StartCondition()) return(FAIL);				// Start condition
		if(!I2C2ByteWrite(slaveAddr)) return(FAIL);			// I2C address - write
		if(!I2C2ByteWrite(MPUREG_MEM_R_W)) return(FAIL);	// internal register address
		IdleI2C2();


		Nop();
		Nop();
		Nop();
		Nop();


		i = MultiByteWriteI2C2(data+bytesWritten, thisLen);		// do all data in array
		I2C2StopWithDelay();									// Stop condition to end reception

		inv_sleep(50);										

		bytesWritten += thisLen;
	}
    return INV_SUCCESS;
}




/**
 *  @brief  used to write multiple bytes of data to the fifo.
 *          This should be sent by I2C.
 *
 *  @param  sl_handle       Unused, pass as NULL
 *  @param  slaveAddr       I2C slave address of device.
 *  @param  length          Length of burst of data.
 *  @param  data            Pointer to block of data.
 *
 *  @return Zero if successful; an error code otherwise
 */
inv_error_t inv_serial_write_fifo( void *sl_handle,
                              unsigned char slaveAddr,
                              unsigned short length, 
                              unsigned char const *data )
{
    int i;
	
	//MPL_LOGV("doing inv_serial_write_fifo\n");

	slaveAddr = slaveAddr << 1;		// shift address to the left by one bit.

			if(!I2C2StartCondition()) return(FAIL);						// Start condition
			if(!I2C2ByteWrite(slaveAddr)) return(FAIL);				// I2C address - write
			if(!I2C2ByteWrite(MPUREG_FIFO_R_W)) return(FAIL);			// internal register address
			IdleI2C2();
			i = MultiByteWriteI2C2(data, length);
			I2C2StopWithDelay();													// Stop condition to end reception
    
    return INV_SUCCESS;
}



/**
 *  @brief  used to read multiple bytes of data from registers.
 *          This should be sent by I2C.
 *
 *  @param  sl_handle       Unused, pass as NULL
 *  @param  slaveAddr       I2C slave address of device.
 *  @param  registerAddr    Register address to read.
 *  @param  length          Length of burst of data.
 *  @param  data            Pointer to block of data.
 *
 *  @return Zero if successful; an error code otherwise
 */
inv_error_t inv_serial_read( void *sl_handle,
						 unsigned char  slaveAddr,
                         unsigned char  registerAddr,
                         unsigned short length,
                         unsigned char  *data )
{
    inv_error_t result;
	int i;
	unsigned char slaveRead;

	//MPL_LOGV("doing inv_serial_read\n");

	slaveAddr = slaveAddr << 1;		// shift address to the left by one bit.
	slaveRead = slaveAddr | 0x01;	// set bit 0 to indicate read

		if(!I2C2StartCondition()) return(FAIL);					// Start condition
		if(!I2C2ByteWrite(slaveAddr)) return(FAIL);				// I2C address - R/W cleared
		if(!I2C2ByteWrite(registerAddr)) return(FAIL);			// internal register address
		IdleI2C2();
		StartI2C2();
		IdleI2C2();
		if(!I2C2ByteWrite(slaveRead)) return(FAIL);				// I2C address - R/W set
		IdleI2C2();												// Make sure bus goes idle
		i = MastergetsI2C2(length,data,50000);		// read out registers
		I2C2StopWithDelay();	
		IdleI2C2();	

    return INV_SUCCESS;
}

/**
 *  @brief  used to read multiple bytes of data from the memory.
 *          This should be sent by I2C.
 *
 *  @param  sl_handle       Unused, pass as NULL
 *  @param  slaveAddr       I2C slave address of device.
 *  @param  memAddr         The location in the memory to read from.
 *  @param  length          Length of burst data.
 *  @param  data            Pointer to block of data.
 *
 *  @return Zero if successful; an error code otherwise
 */
inv_error_t inv_serial_read_mem( void *sl_handle,
							unsigned char  slaveAddr, 
                            unsigned short memAddr, 
                            unsigned short length, 
                            unsigned char *data )
{
inv_error_t result;
	unsigned char tmpAddr;
	unsigned char memAddress[1];
    uint_fast16_t bytesRead = 0;
	int i;
	unsigned char slaveRead, bankAddr, regAddr;

	//MPL_LOGV("doing inv_serial_read_mem\n");

	slaveAddr = slaveAddr << 1;		// shift address to the left by one bit.
	slaveRead = slaveAddr | 0x01;	// set bit 0 to indicate read
   
	/* Write bank - first time only */
    tmpAddr = MPUREG_BANK_SEL;
    memAddress[0] = memAddr >> 8;
	bankAddr = memAddr >> 8;

	if(!I2C2StartCondition()) return(FAIL);				// Start condition
	if(!I2C2ByteWrite(slaveAddr)) return(FAIL);			// I2C address - write
	if(!I2C2ByteWrite(tmpAddr)) return(FAIL);			// Bank select register address 
	if(!I2C2ByteWrite(bankAddr)) return(FAIL);			// data for bank select register
	I2C2StopWithDelay();											// Stop
	IdleI2C2();

	while (bytesRead < length)
	{

		Nop();
		Nop();
		Nop();

		unsigned short thisLen = min(SERIAL_MAX_TRANSFER_SIZE, length-bytesRead);

		tmpAddr = MPUREG_MEM_START_ADDR;
		regAddr = (memAddr & 0xff) + bytesRead;

		if(!I2C2StartCondition()) return(FAIL);			// Start condition
		if(!I2C2ByteWrite(slaveAddr)) return(FAIL);		// I2C address - write
		if(!I2C2ByteWrite(tmpAddr)) return(FAIL);		// internal register address
		if(!I2C2ByteWrite(regAddr)) return(FAIL);		// internal register address

		I2C2StopWithDelay();										// Stop
		IdleI2C2();									

		Nop();
		Nop();
		Nop();


		if(!I2C2StartCondition()) return(FAIL);			// Start condition	
		if(!I2C2ByteWrite(slaveAddr)) return(FAIL);		// I2C address - R/W cleared
		if(!I2C2ByteWrite(MPUREG_MEM_R_W)) return(FAIL);		// internal register address
		IdleI2C2();
		StartI2C2();
		IdleI2C2();
		if(!I2C2ByteWrite(slaveRead)) return(FAIL);		// I2C address - R/W set
		IdleI2C2();										// Make sure bus goes idle
		i = MastergetsI2C2(thisLen,data+bytesRead,50000);		// read out registers
		I2C2StopWithDelay();	
		IdleI2C2();	


		bytesRead += thisLen;
	}	
	return INV_SUCCESS;    
}


/**
 *  @brief  used to read multiple bytes of data from the fifo.
 *          This should be sent by I2C.
 *
 *  @param  sl_handle       Unused, pass as NULL
 *  @param  slaveAddr       I2C slave address of device.
 *  @param  length          Number of bytes to read from fifo.
 *  @param  data            Pointer to write fifo data.
 *
 *  @return Zero if successful; an error code otherwise
 */
inv_error_t inv_serial_read_fifo( void *sl_handle,
							 unsigned char  slaveAddr, 
                             unsigned short length, 
                             unsigned char *data )
{
     uint16_t bytesRead = 0;
    inv_error_t result;
	unsigned char slaveRead;
	int i;

	//MPL_LOGV("doing inv_serial_read_fifo\n");

	slaveAddr = slaveAddr << 1;		// shift address to the left by one bit.
	slaveRead = slaveAddr | 0x01;	// set bit 0 to indicate read


			if(!I2C2StartCondition()) return(FAIL);						// Start condition
			if(!I2C2ByteWrite(slaveAddr)) return(FAIL);				// I2C address - write
			if(!I2C2ByteWrite(MPUREG_FIFO_R_W)) return(FAIL);			// internal register address

			IdleI2C2();
			StartI2C2();
			IdleI2C2();
			if(!I2C2ByteWrite(slaveRead)) return(FAIL);		// I2C address - R/W set
			IdleI2C2();		

			i = MastergetsI2C2(length,data, 5000);		// read out registers
			I2C2StopWithDelay();			

    return INV_SUCCESS;
}

/**
 *  @brief  used to get the calibration data.
 *          It is called by the MPL to get the calibration data used by the 
 *          motion library.
 *          This data would typically be saved in non-volatile memory.
 *
 *  @param  cfg     Pointer to the calibration data.
 *  @param  len     Length of the calibration data.
 *
 *  @return INV_SUCCESS if successful, a non-zero error code otherwise.
 */
inv_error_t inv_serial_read_cal( unsigned char *cal, unsigned int  len )
{
    /* UMPL does not implement the inv_serial_read_cal function.*/
    return INV_ERROR_FEATURE_NOT_IMPLEMENTED;
}

/**
 *  @brief  Get the calibration length.
 *  @param  len 
 *              lenght to be returned
 *  @return INV_SUCCESS if successful, a non-zero error code otherwise.
 */
inv_error_t inv_serial_get_cal_length(unsigned int *len)
{
    /* UMPL does not implement the inv_serial_get_cal_length function.*/
    return INV_ERROR_FEATURE_NOT_IMPLEMENTED;
}

/**
 *  @brief  used to save the calibration data.
 *          It is called by the MPL to save the calibration data used by the 
 *          motion library.
 *          This data would typically be saved in non-volatile memory.
 *
 *  @param cfg  Pointer to the calibration data.
 *  @param len  Length of the calibration data.
 *
 *  @return INV_SUCCESS if successful, a non-zero error code otherwise.
 */
inv_error_t inv_serial_write_cal( unsigned char *cal, unsigned int len )
{
    /* UMPL does not implement the inv_serial_write_cal function.*/
    return INV_ERROR_FEATURE_NOT_IMPLEMENTED;
}

void I2C2StopWithDelay()
{
unsigned char delayCount;

	for(delayCount = 0; delayCount < 100; delayCount++ )		// I need a delay before I do the stop condition.
	{
		Nop();
	}

	StopI2C2();

	#ifdef DEBUGI2C
	inv_sleep(20);
	#endif

}

