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



int main(int argc, char** argv) {
    USBInitialize();

    int i = 1;

    while(TRUE) {

        USBDeviceTasks();


        char buffer[64];
        getsUSBUSART(buffer, 64);

        if(USBUSARTIsTxTrfReady()) {
            switch(i) {
                case 0:
                    putrsUSBUSART("Ab\r\n");
                    i++;
                    break;
                case 1:
                    putrsUSBUSART("cdE\r\n");
                    i = 0;
                    break;
                default:
                    i--;
                    break;
            }


            //CDCTxService();
        }

        CDCTxService();
    }

    return (EXIT_SUCCESS);
}

