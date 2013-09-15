#include <p32xxxx.h>

#include "i2c_mpu.h"
#include "HardwareProfile - PIC32MX795F512L PIM.h"

#include "Microchip/USB/usb.h"
#include "Microchip/USB/usb_device.h"
#include "Microchip/USB/usb_function_cdc.h"

#include "msg_buffer.h"

void I2C_init() {
    int actualClock;

    I2CConfigure(I2C_DEV, 0);

    actualClock = I2CSetFrequency(I2C_DEV, GetPeripheralClock(), I2C_SPEED);
    if(abs(actualClock-I2C_SPEED) > I2C_SPEED*0.1) {
        appendBuffer("ERROR: Could not set I2C clock\r\n");
    } else {
        appendBuffer("INFO: I2C Clock set\r\n");
    }
    
    I2CEnable(I2C_DEV, TRUE);
    appendBuffer("INFO: I2C Enabled\r\n");
}