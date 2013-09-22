#include <p32xxxx.h>

#include "i2c_mpu.h"
#include "HardwareProfile - PIC32MX795F512L PIM.h"

#include "Microchip/USB/usb.h"
#include "Microchip/USB/usb_device.h"
#include "Microchip/USB/usb_function_cdc.h"

#include "eMPL/inv_mpu.h"

#include "msg_buffer.h"
#include "eMPL/inv_mpu.h"

/*******************************************************************************
  Function:
    BOOL StartTransfer( BOOL restart )

  Summary:
    Starts (or restarts) a transfer to/from the EEPROM.

  Description:
    This routine starts (or restarts) a transfer to/from the EEPROM, waiting (in
    a blocking loop) until the start (or re-start) condition has completed.

  Precondition:
    The I2C module must have been initialized.

  Parameters:
    restart - If FALSE, send a "Start" condition
            - If TRUE, send a "Restart" condition

  Returns:
    TRUE    - If successful
    FALSE   - If a collision occured during Start signaling

  Example:

    StartTransfer(FALSE);


  Remarks:
    This is a blocking routine that waits for the bus to be idle and the Start
    (or Restart) signal to complete.
  *****************************************************************************/

BOOL StartTransfer( BOOL restart )
{
    I2C_STATUS  status;

    // Send the Start (or Restart) signal
    if(restart)
    {
        I2CRepeatStart(I2C2);
    }
    else
    {
        // Wait for the bus to be idle, then start the transfer
        while( !I2CBusIsIdle(I2C2) );

        if(I2CStart(I2C2) != I2C_SUCCESS)
        {
            DBPRINTF("Error: Bus collision during transfer Start\n");
            return FALSE;
        }
    }

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(I2C2);

    } while ( !(status & I2C_START) );

    return TRUE;
}

/*******************************************************************************
  Function:
    BOOL TransmitOneByte( UINT8 data )

  Summary:
    This transmits one byte to the EEPROM.

  Description:
    This transmits one byte to the EEPROM, and reports errors for any bus
    collisions.

  Precondition:
    The transfer must have been previously started.

  Parameters:
    data    - Data byte to transmit

  Returns:
    TRUE    - Data was sent successfully
    FALSE   - A bus collision occured

  Example:

    TransmitOneByte(0xAA);


  Remarks:
    This is a blocking routine that waits for the transmission to complete.
  *****************************************************************************/

BOOL TransmitOneByte( UINT8 data )
{
    // Wait for the transmitter to be ready
    while(!I2CTransmitterIsReady(I2C2));

    // Transmit the byte
    if(I2CSendByte(I2C2, data) == I2C_MASTER_BUS_COLLISION)
    {
        DBPRINTF("Error: I2C Master Bus Collision\n");
        return FALSE;
    }

    // Wait for the transmission to finish
    while(!I2CTransmissionHasCompleted(I2C2));

    return TRUE;
}

/*******************************************************************************
  Function:
    void StopTransfer( void )

  Summary:
    Stops a transfer to/from the EEPROM.

  Description:
    This routine Stops a transfer to/from the EEPROM, waiting (in a
    blocking loop) until the Stop condition has completed.

  Precondition:
    The I2C module must have been initialized & a transfer started.

  Parameters:
    None.

  Returns:
    None.

  Example:

    StopTransfer();


  Remarks:
    This is a blocking routine that waits for the Stop signal to complete.
  *****************************************************************************/

void StopTransfer( void )
{
    I2C_STATUS  status;

    // Send the Stop signal
    I2CStop(I2C2);

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(I2C2);

    } while ( !(status & I2C_STOP) );
}


int i2c_write(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data) {
    while( !I2CBusIsIdle(I2C2) );
    StartTransfer(FALSE);
    TransmitOneByte((addr<<1) & 0b11111110);
    TransmitOneByte(reg);

    int i;
    for(i = 0; i < length; i++) {
        TransmitOneByte(data[i]);
    }
    StopTransfer();

    return 0;
}

int i2c_read(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data) {
    StartTransfer(FALSE);
    TransmitOneByte((addr<<1) & 0b11111110);
    TransmitOneByte(reg);
    
    StartTransfer(TRUE);
    TransmitOneByte((addr<<1) | 0b00000001);
    
    int i;
    for(i = 0; i < length; i++) {
        I2CReceiverEnable(I2C2, TRUE);
	while(!I2CReceivedDataIsAvailable(I2C2));
        if(i == length-1) {
            I2CAcknowledgeByte(I2C2, FALSE);
        } else {
            I2CAcknowledgeByte(I2C2, TRUE);
        }

        data[i] = I2CGetByte(I2C2);
        IdleI2C2();

    }
    StopTransfer();
    return 0;
}

int get_ms(unsigned long *count) {
    *count = 7; //@todo: implement the clock counter
}


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

    /*if(!StartTransfer(FALSE)) {
        while(1);
    }
    
    if(!TransmitOneByte((0x68 << 1) & 0b11111110)) {
        while(1);
    }

    if(!I2CByteWasAcknowledged(I2C_DEV)) {
        while(1);
    }

    TransmitOneByte(0x75);


    if(!I2CByteWasAcknowledged(I2C_DEV)) {
        while(1);
    }

    if(!StartTransfer(TRUE)) {
        while(1);
    }
    TransmitOneByte((0x68 << 1) | 0b00000001);

    if(!I2CByteWasAcknowledged(I2C_DEV)) {
        while(1);
    }

    I2CReceiverEnable(I2C_DEV, TRUE);
    while(!I2CReceivedDataIsAvailable(I2C_DEV));
    I2CAcknowledgeByte(I2C_DEV, FALSE);
    I2CGetByte(I2C_DEV);
    StopTransfer();*/
}