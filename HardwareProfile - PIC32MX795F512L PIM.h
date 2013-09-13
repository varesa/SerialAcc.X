/********************************************************************
 FileName:      HardwareProfile - PIC32MX795F512L PIM.h
 Dependencies:  See INCLUDES section
 Processor:     PIC32 USB Microcontrollers
 Hardware:      PIC32MX795F512L PIM
 Compiler:      Microchip C32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC32MX795F512L_PIM_H
#define HARDWARE_PROFILE_PIC32MX795F512L_PIM_H

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/


	/*******************************************************************/
	/******** USB stack hardware selection options *********************/
	/*******************************************************************/
	//This section is the set of definitions required by the MCHPFSUSB
	//  framework.  These definitions tell the firmware what mode it is
	//  running in, and where it can find the results to some information
	//  that the stack needs.
	//These definitions are required by every application developed with
	//  this revision of the MCHPFSUSB framework.  Please review each
	//  option carefully and determine which options are desired/required
	//  for your application.
	
	//#define USE_SELF_POWER_SENSE_IO
//	#define tris_self_power     TRISAbits.TRISA2    // Input
	#define self_power          1
	
	//#define USE_USB_BUS_SENSE_IO
//	#define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
	#define USB_BUS_SENSE       1 

    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

// this is the address of flash where web configurations will be stored
#define	APP_CONFIG_ADDRESS	0x1D004000

#define SYS_CLOCK 					(80000000ul)
#define GetSystemClock()            (SYS_CLOCK)
#define GetPeripheralClock()        (SYS_CLOCK/2)
#define GetInstructionClock()       (SYS_CLOCK)

/*********************************************************************
* IOS FOR THE DISPLAY CONTROLLER
*********************************************************************/

	#define	GFX_USE_DISPLAY_CONTROLLER_ILI9320

	#define	USE_GFX_PMP
	#define	USE_GOL
	// SPP Unfinished values
	#define	PMP_DATA_SETUP_TIME	10
	#define	PMP_DATA_WAIT_TIME	10
	#define	PMP_DATA_HOLD_TIME	10

	// Definitions for reset pin
	//#define RST_TRIS_BIT    TRISAbits.TRISA7
	//#define RST_LAT_BIT     LATAbits.LATA7
	#define	DisplayResetEnable()	LATAbits.LATA7 = 0
	#define	DisplayResetDisable()	LATAbits.LATA7 = 1
	#define	DisplayResetConfig()	TRISAbits.TRISA7 = 0
	
	
	// Definitions for RS pin
	//#define RS_TRIS_BIT TRISAbits.TRISA10
	//#define RS_LAT_BIT  LATAbits.LATA10
	#define	DisplaySetCommand()		LATAbits.LATA10 = 0
	#define	DisplaySetData()		LATAbits.LATA10 = 1
	#define	DisplayCmdDataConfig()	TRISAbits.TRISA10 = 0
	
	// Definitions for CS pin
	//#define CS_TRIS_BIT TRISAbits.TRISA9
	//#define CS_LAT_BIT  LATAbits.LATA9
	#define	DisplayEnable()			LATAbits.LATA9 = 0
	#define	DisplayDisable()		LATAbits.LATA9 = 1
	#define	DisplayConfig()			TRISAbits.TRISA9 = 0

	// Definitions for POWER ON pin (for the BACK LIGHT)
	//#define POWERON_LAT_BIT     LATDbits.LATD3
	//#define POWERON_TRIS_BIT    TRISDbits.TRISD3
	#define DisplayBacklightConfig()    TRISDbits.TRISD3 = 0  // pin modified for MMB PIC32MX7
	#define DisplayBacklightOn()        LATDbits.LATD3 = 1
	#define DisplayBacklightOff()       LATDbits.LATD3 = 0


	// Definitions for POWER ON pin (NOT USED)
	#define DisplayPowerConfig()       
	#define DisplayPowerOn()           
	#define DisplayPowerOff()

/*********************************************************************
* RTCC DEFAULT INITIALIZATION (these are values to initialize the RTCC
*********************************************************************/
    #define RTCC_DEFAULT_DAY        01      // 1
    #define RTCC_DEFAULT_MONTH      01      // January
    #define RTCC_DEFAULT_YEAR       13      // 2013
    #define RTCC_DEFAULT_WEEKDAY    02      // Tuesday
    #define RTCC_DEFAULT_HOUR       00      // 10:10:01
    #define RTCC_DEFAULT_MINUTE     00
    #define RTCC_DEFAULT_SECOND     00


/* External SMSC PHY configuration */
	#define	PHY_RMII				// external PHY runs in RMII mode
	#define	PHY_CONFIG_ALTERNATE	// alternate configuration used
	#define	PHY_ADDRESS			0x1	// the address of the National DP83848 PHY

	
	// I/O pins
	#define LED0_TRIS			(TRISBbits.TRISB10)	// LED 1
	#define LED0_IO				(PORTBbits.RB10)
	#define	LED1_TRIS			(TRISDbits.TRISD1)	// LED 2
	#define LED1_IO				(PORTDbits.RD1)
	#define	LED2_TRIS			(TRISDbits.TRISD2)	// LED 3
	#define	LED2_IO				(PORTDbits.RD2)
	#define LED3_TRIS			(TRISGbits.TRISG12)	// RELAY 1
	#define LED3_IO				(PORTGbits.RG12)
	#define LED4_TRIS			(TRISGbits.TRISG13)	// RELAY 2
	#define LED4_IO				(PORTGbits.RG13)

	#define BUTTON0_TRIS		(TRISDbits.TRISD6)	// AKA BUT1
	#define	BUTTON0_IO			(PORTDbits.RD6)
	#define BUTTON1_TRIS		(TRISDbits.TRISD7)	// AKA BUT2
	#define	BUTTON1_IO			(PORTDbits.RD7)
	#define BUTTON2_TRIS		(TRISDbits.TRISD13)	// AKA BUT3
	#define	BUTTON2_IO			(PORTDbits.RD13)
	#define BUTTON3_TRIS		(TRISGbits.TRISG7)	// AKA IN1
	#define	BUTTON3_IO			(PORTGbits.RG7)
	#define BUTTON4_TRIS		(TRISGbits.TRISG6)	// AKA IN2
	#define	BUTTON4_IO			(PORTGbits.RG6)

	#define LED_PUT(a)			LED0_IO = !!(a & 0x01);\
								LED1_IO = !!(a & 0x02);\
								LED2_IO = !!(a & 0x04);\
								LED3_IO = !!(a & 0x08);\
								LED4_IO = !!(a & 0x10);\
								LED5_IO = !!(a & 0x20);\
								LED6_IO = !!(a & 0x40);\
								LED7_IO = !!(a & 0x80);\


#endif  //HARDWARE_PROFILE_PIC32MX795F512L_PIM_H
