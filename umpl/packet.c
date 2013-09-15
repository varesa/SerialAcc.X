
/*
 $License:
    Copyright (C) 2010 InvenSense Corporation, All Rights Reserved.
 $
 */
/******************************************************************************
 *
 * $Id: packet.c 4/14/2011 10:17:57 AM  phickey $
 *
 *****************************************************************************/

/** 
 *  @defgroup DATA-CLIENT
 *  @brief  Data Client Implementation.
 *          Provides a mechanism to send and receive packetized data.
 *
 *  @{
 *      @file   packet.c
 *      @brief  Implements a mechanism to send and receive packetized data
 *              over the USB CDC port. Depends on the ASF usb_cdc service
 *              and the cpu cycle_counter driver.
 *				
**/

/* ------------------ */
/* - Include Files. - */
/* ------------------ */
#include <asf.h>
#include "cycle_counter.h"
#include "packet.h"

/* --------------- */
/* -  Functions. - */
/* --------------- */

/**
 *  @brief sendPacket sends a 14-byte packet in a specific format on the udi_cdc port.
 *		   It Checks for timeout on a per-byte basis. Out of the 14 bits, 10 bits are 
 *		   for payload and the rest are for control.
 *		   The format of each packet is as follows:
 *			<center>packet[0] = $</center>
 *			<center>packet[1] = DATA_TYPE</center>
 *			<center>packet[2] to packet[12] = DATA</center>
 *			<center>packet[13] = '\\r'</center>
 *			<center>packet[14] = '\\n'</center>
 *
 *
 *  @return 0 if successful; non-zero if timed out
 */
int sendPacket(unsigned char type, unsigned char * payload)
{
    t_cpu_time timer;
    unsigned long cpu_hz = sysclk_get_cpu_hz();
    unsigned long tenms = cpu_ms_2_cy(10,cpu_hz);

    unsigned char out[14];
    char ii;

    out[0] = '$';
    out[1] = type;
    for (ii = 2; ii < 12; ii++)
        out[ii] = payload[ii-2];
    out[12] = '\r';
    out[13] = '\n';

    for (ii = 0; ii < 14; ii++)
    {
        cpu_set_timeout(tenms,&timer);
        do {} while ((!udi_cdc_is_tx_ready()) && !cpu_is_timeout(&timer));
        if (udi_cdc_is_tx_ready())
            udi_cdc_putc(out[ii]);
        else
            return -1;
    }
    return 0;
}
/**
 *  @brief Once a request for data has been made to the daemon, the getPacket is
 *		   used to receive packets. It implements an automatic time out to prevent
 *		   a "blocked" state.
 *
 *  @return 0 if successful; non-zero if timed out
 */
int getPacket(unsigned char *type, unsigned char * payload)
{
	t_cpu_time timer;
    unsigned long cpu_hz = sysclk_get_cpu_hz();
    unsigned long hundms = cpu_ms_2_cy(100,cpu_hz);
	unsigned long threesec = cpu_ms_2_cy(3000,cpu_hz);

	int ii;
	unsigned char in[14];

    /* block for up to 3 seconds until $ is received */
	cpu_set_timeout(threesec,&timer);
	do {
		do {} while ((!udi_cdc_is_rx_ready()) && !cpu_is_timeout(&timer));
		if (udi_cdc_is_rx_ready())
			in[0] = udi_cdc_getc();
			// if in[0] '$', we'll continue onto the following for loop
			// if not, continue waiting for another char.
		else
			return -2;
	} while (in[0] != '$');

    for (ii = 1; ii < 14; ii++)
    {
        cpu_set_timeout(hundms,&timer);
        do {} while ((!udi_cdc_is_rx_ready()) && !cpu_is_timeout(&timer));
        if (udi_cdc_is_rx_ready())
            in[ii] = udi_cdc_getc();
        else
            return -1;
    }

	*type = in[1];
	for (ii = 0; ii < 10; ii++)
		payload[ii] = in[ii+2];

    return 0;
}
