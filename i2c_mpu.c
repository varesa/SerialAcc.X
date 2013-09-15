#include <p32xxxx.h>

#include "i2c_mpu.h"
#include "HardwareProfile - PIC32MX795F512L PIM.h"

#include "Microchip/USB/usb.h"
#include "Microchip/USB/usb_device.h"
#include "Microchip/USB/usb_function_cdc.h"

//  Motion library includes
#include "umpl/ml.h"
#include "umpl/mldl.h"
//#include "ml_stored_data.h"
#include "umpl/mlmath.h"
#include "umpl/packet.h"
#include "umpl/mltypes.h"
#include "umpl/mlos.h"
#include "umpl/mldl_cfg.h"
#include "umpl/umpl-states.h"

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

inv_error_t result = INV_SUCCESS;

#define LIGHT   0x01
#undef SUCCESS
#define	SUCCESS		0x1
#define	FAIL		0x0
#define SERIAL_TIMEOUT_VALUE 0x4000
#define NO_SECURITY 0x0

/**************************************************************************************
Function Prototype : char MultiByteWriteI2C2(unsigned char *wrptr)

Description        : This function is used to write out a data string to the I2C bus,
					and is terminated when # characters written = datalength

Arguments          : wrptr - Character type pointer to data objects in RAM. The data
                     objects are written to the I2C device.

Return Value       : This function returns -3 if a write collision occurred.
                     This function returns 0 if the null character was reached
                     in data string.

Remarks            : This routine writes a stream of data to the I2C bus.
**************************************************************************************/
char MultiByteWriteI2C2(char *wrptr, unsigned short dataLength)
{
unsigned short bytesWritten = 0;

    while(bytesWritten < dataLength)                           //transmit data until null char
    {
        if(MasterputcI2C2(*wrptr) == -1)        // write a byte
        return -3;                          //return with write collison error

        while(I2C2STATbits.TBF);             //Wait until data is transmitted.

        IdleI2C2();
		bytesWritten++;
        wrptr++;
    }
    return 0;
}



BOOL I2C2StartCondition()
{
	int timeout_counter = 0;

   	IdleI2C2();
   	StartI2C2();
   	while(I2C2CONbits.SEN)
	{
		timeout_counter++;
		if(timeout_counter>SERIAL_TIMEOUT_VALUE)
		{
			return(FAIL);
		}
	}
return(SUCCESS);
}


BOOL I2C2ByteWrite(char dataOut)
{
	int	timeout_counter = 0;

	IdleI2C2();									// Make sure that bus is idle
   	MasterWriteI2C2(dataOut);					// Send out data on bus
	while(I2C2STATbits.TBF)						// Wait until TX buffer is empty
	{
		timeout_counter++;
		if(timeout_counter>SERIAL_TIMEOUT_VALUE)
		{
			return(FAIL);
		}
	}

	timeout_counter = 0;
        mI2C2ClearAllIntFlags();
   	//IFS3bits.MI2C2IF = 0;
   	while(I2C2STATbits.ACKSTAT)					// Make sure I get an acknowledge
	{
		timeout_counter++;
		if(timeout_counter>SERIAL_TIMEOUT_VALUE)
		{
			return(FAIL);
		}
	}
return(SUCCESS);
}

//static inline
void platform_init(void)
{
	result = umplInit(NULL);
	if (result != INV_SUCCESS)
			MPL_LOGE("umplStartMPU Error %d\n", result);
	result = umplStartAccelOnly(200.0f);				// 200 Hz operation
	result = umplStartMPU();

			MPL_LOGE("umplStartMPU returned: %d\n", result);
	//inv_self_test_run();		// Added 11/14/2011 to eliminate drift problem
}