#include <xc.h>
#include <p32xxxx.h>
#include <sys/attribs.h>

#include "i2c_mpu.h"
#include "HardwareProfile - PIC32MX795F512L PIM.h"

#include "Microchip/USB/usb.h"
#include "Microchip/USB/usb_device.h"
#include "Microchip/USB/usb_function_cdc.h"

#include "eMPL/inv_mpu.h"

#include "msg_buffer.h"
#include "eMPL/inv_mpu.h"


enum HWSTATE HWState;
enum STAGE Stage;
struct PACKAGE Package;
int DATA_READY;

void __ISR(_I2C2_VECTOR, IPL7AUTO) I2CInterrupt(void) {
    switch(HWState) {
        case START:
            HWState = TRANSMIT;
            ACTION_REQUIRED = 1;
            break;
        case TRANSMIT:
            if (Package.index > Package.length) {
                HWState = STOP;
            }
            ACTION_REQUIRED = 1;
            break;
        case STOP:
            HWState = IDLE;
            break;
    }

    INTClearFlag(INT_I2C2);
}

void I2C_init() {

    I2C2CONbits.ON = 1; // Enable I2C2
    I2C2BRG = 90;       // Set speed to 400 kH

    HWState = IDLE;
    DATA_READY = 0;
    ACTION_REQUIRED = 0;

    INTEnable(INT_I2C2, TRUE);
}

void I2C_Tasks() {
    if(!(DATA_READY || ACTION_REQUIRED)) {
        return; // Nothing to do
    }

    if(DATA_READY) {
        if(HWState == IDLE) {
            DATA_READY = 0;
            HWState = START;
        }
    }

    switch(HWState) {
        case START:
            I2C2CONbits.SEN = 1;
            break;
        case TRANSMIT:
            I2C2TRN = Package.data[Package.index];
            break;
        case STOP:
            I2C2CONbits.PEN = 1;
            break;
    }
}

int i2c_write(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data) {
    while(HWState != IDLE) {
        I2C_Tasks();
    }

    Package.address = addr;
    Package.reg = reg;
    Package.data = data;
    Package.length = length;
    Package.direction = WRITE;

    Stage = ADDRESS;

    DATA_READY = 1;

    I2C_Tasks();
    while(HWState != IDLE) {
        I2C_Tasks();
    }
    /*while( !I2CBusIsIdle(I2C2) ); //@todo: implement I2c error checking
    StartTransfer(FALSE);
    //TransmitOneByte((addr<<1) WRITE);
    TransmitOneByte(addr);
    StopTransfer();
    return 0;

    TransmitOneByte(reg);

    int i;
    for(i = 1; i <= length; i++) {
        //TransmitOneByte((*data>>(length-i)*8) & 255);
        TransmitOneByte(data[0]);
        if(i != length) {
            *data = *data<<8;
        }
    }
    StopTransfer();

    return 0;*/
}

int i2c_read(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data) {
    /*StartTransfer(FALSE);
    TransmitOneByte(addr);// << 1 WRITE);
    TransmitOneByte(reg);
    StartTransfer(TRUE);
    
    int i;
    for(i = 1; i <= length; i++) {
        I2CReceiverEnable(I2C2, TRUE);
	while(!I2CReceivedDataIsAvailable(I2C2));
        if(i == length) {
            I2CAcknowledgeByte(I2C2, FALSE);
        } else {
            I2CAcknowledgeByte(I2C2, TRUE);
        }
        
        //*data = *data | I2CGetByte(I2C2);
        unsigned char byte = I2CGetByte(I2C2);
        data[i] = &byte;

        if(i != length) {
            //*data = *data<<8;
        } else {
            I2CStop(I2C2);
        }
    }
    return 0;*/
}

int get_ms(unsigned long *count) {
    *count = 7; //@todo: implement the clock counter
}