/* 
 * File:   main.c
 * Author: esa
 *
 * Created on September 12, 2013, 3:45 PM
 */

#include "Microchip/TimeDelay.h"


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

struct rx_s {
    unsigned char header[3];
    unsigned char cmd;
};
struct hal_s {
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short report;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
    struct rx_s rx;
};
static struct hal_s hal = {0};

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

int main(int argc, char** argv) {
    #if defined(__32MX460F512L__)|| defined(__32MX795F512L__)
    // Configure the PIC32 core for the best performance
    // at the operating frequency. The operating frequency is already set to
    // 60MHz through Device Config Registers
    SYSTEMConfigPerformance(60000000);
    #endif
    USBDeviceInit();

    int mpu_init_stage = 0;

    int i = 0;
    int j = 0;

    unsigned short gyro_rate, gyro_fsr;
    unsigned char accel_fsr;

    while((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) {
        USBDeviceTasks();
    }
    
    CDCTxService();
    
    while(i < 1000000) {   // A delay to work around something
        i++;            // (Slowness in terminal program?)
        USBDeviceTasks();
        CDCTxService();
    }

    while(TRUE) {

        USBDeviceTasks();
        if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;

        CDCTxService();

        switch (mpu_init_stage) {
            case 0:
                appendBuffer("INFO: USB Accelerometer started up\r\n");
                I2C_init();
                mpu_init((void *)0);
                appendBuffer("INFO: MPU Initialization stage 1 complete\r\n");

                mpu_init_stage = 1;
                break;
            case 1:
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
                appendBuffer("INFO: MPU Initialization stage 2 complete\r\n");

                mpu_init_stage = 2;
                break;
            case 2:
                dmp_load_motion_driver_firmware();
                dmp_set_orientation(
                    inv_orientation_matrix_to_scalar(gyro_orientation));
                //dmp_register_tap_cb(tap_cb);
                //dmp_register_android_orient_cb(android_orient_cb);
                //hal.dmp_features = DMP_FEATURE_SEND_CAL_GYRO;
                hal.dmp_features = DMP_FEATURE_6X_LP_QUAT;
                //hal.dmp_features = DMP_FEATURE_6X_LP_QUAT; //| DMP_FEATURE_TAP |
                //    DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
                //    DMP_FEATURE_GYRO_CAL;
                dmp_enable_feature(hal.dmp_features); //@todo: look into HAL
                dmp_set_fifo_rate(100);
                mpu_set_dmp_state(1);
                hal.dmp_on = 1;
                appendBuffer("INFO: MPU Initialization stage 3 complete\r\n");
                appendBuffer("01234567891011121314151617181920\r\n");

                mpu_init_stage = 3;
                break;
            case 3:
            {
                short gyro[3];
                short accel[3];
                long quat[4];
                unsigned long timestamp;
                short sensors;
                unsigned char more;
                /*int a = gyro[0];
                int b = gyro[1];
                int c = gyro[2];*/

                int a = quat[0];
                int b = quat[1];
                int c = quat[2];
                int d = quat[3];

                if(dmp_read_fifo(gyro, accel, quat, &timestamp, &sensors, &more) == 0) {
                    if(!(sensors & INV_WXYZ_QUAT)) {
                        break;
                    }
                    usbPrintf("Q %i %i %i %i\r\n", a, b, c, d);
                    
                    /*if(!(sensors & INV_XYZ_GYRO)) {
                        break;
                    }
                    usbPrintf("G %i %i %i\r\n", a, b, c);*/
                }
                break;
            }
        }


        /*if(j > 10000) {
            j = 0;
            appendBuffer("Test\r\n");
            Delay10us(10);
        } else {
            j++;
        }*/


        while(!USBUSARTIsTxTrfReady()) {
            USBDeviceTasks();
            CDCTxService();
        }

        if(dataInBuffer) {
            char tmp[1024] ={0};
            sprintf(tmp, "%s", msg_buffer);
            putrsUSBUSART(tmp);
            //putrsUSBUSART(msg_buffer);

            //msg_buffer[0] = '\0';
            memset(&msg_buffer[0], 0, sizeof(msg_buffer));
            //strcpy(msg_buffer, "");
            dataInBuffer = FALSE;
        }

        
    }

    return (EXIT_SUCCESS);
}

