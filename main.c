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


#include "i2c_mpu.h"
#include "HardwareProfile - PIC32MX795F512L PIM.h"



int main(int argc, char** argv) {
    #if defined(__32MX460F512L__)|| defined(__32MX795F512L__)
    // Configure the PIC32 core for the best performance
    // at the operating frequency. The operating frequency is already set to
    // 60MHz through Device Config Registers
    SYSTEMConfigPerformance(60000000);
    #endif
    USBDeviceInit();

    BOOL mpu_uninitialized = TRUE;

    int i = 0;

    while(TRUE) {

        USBDeviceTasks();
        if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;

        CDCTxService();

        if(i < 1000000) {   // A delay to work around something
            i++;            // (Slowness in terminal program?)
            continue;
        }

        if(mpu_uninitialized) {
            //if(!USBUSARTIsTxTrfReady()) continue;
            appendBuffer("INFO: USB Accelerometer started up\r\n");
            I2C_init();
            mpu_uninitialized = FALSE;
        }

        if(USBUSARTIsTxTrfReady()) {
            if(dataInBuffer) {
                putrsUSBUSART(msg_buffer);
                dataInBuffer = FALSE;
            }
        }
        
    }

    return (EXIT_SUCCESS);
}

