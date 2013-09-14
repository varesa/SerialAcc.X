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

#include "configwords.h"



int main(int argc, char** argv) {
    USBInitialize();

    while(TRUE) {

        USBDeviceTasks();
    }

    return (EXIT_SUCCESS);
}

