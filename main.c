/* 
 * File:   main.c
 * Author: esa
 *
 * Created on September 12, 2013, 3:45 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "Microchip/Compiler.h"
#include "Microchip/GenericTypeDefs.h"

#include "Microchip/USB/usb_common.h"
#include "Microchip/USB/usb_device.h"
#include "Microchip/USB/usb_function_cdc.h"

#include "configwords.h"
#include "usb_config.h"
#include "msg_buffer.h"

#include "eMPL/inv_mpu.h"
#include "eMPL/inv_mpu_dmp_motion_driver.h"

#include "i2c_mpu.h"
#include "HardwareProfile - PIC32MX795F512L PIM.h"

/* The sensors can be mounted onto the board in any orientation. The mounting
 * matrix seen below tells the MPL how to rotate the raw data from thei
 * driver(s).
 * TODO: The following matrices refer to the configuration on an internal test
 * board at Invensense. If needed, please modify the matrices to match the
 * chip-to-body matrix for your particular set up.
 */
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static inline unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static inline unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}

void initSensor() {
        unsigned short gyro_rate, gyro_fsr;
    unsigned char accel_fsr;

    //if(!USBUSARTIsTxTrfReady()) continue;
    appendBuffer("INFO: USB Accelerometer started up\r\n");
    I2C_init();
    mpu_init((void *)0);

    /* Get/set hardware configuration. Start gyro. */
    /* Wake up all sensors. */
    mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    /* Push both gyro and accel data into the FIFO. */
    mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    mpu_set_sample_rate(100);
    /* Read back configuration in case it was set improperly. */
    mpu_get_sample_rate(&gyro_rate);
    mpu_get_gyro_fsr(&gyro_fsr);
    mpu_get_accel_fsr(&accel_fsr);

    dmp_load_motion_driver_firmware();
    dmp_set_orientation(
        inv_orientation_matrix_to_scalar(gyro_orientation));
    //dmp_register_tap_cb(tap_cb);
    //dmp_register_android_orient_cb(android_orient_cb);
    //hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | //DMP_FEATURE_TAP |
    //    DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
    //    DMP_FEATURE_GYRO_CAL;
    //dmp_enable_feature(hal.dmp_features); //@todo: look into HAL
    dmp_set_fifo_rate(100);
    mpu_set_dmp_state(1);
    //hal.dmp_on = 1;
}

int main(int argc, char** argv) {
    #if defined(__32MX460F512L__)|| defined(__32MX795F512L__)
    // Configure the PIC32 core for the best performance
    // at the operating frequency. The operating frequency is already set to
    // 60MHz through Device Config Registers
    SYSTEMConfigPerformance(60000000);
    #endif

    initSensor();

    return (EXIT_SUCCESS);
}

