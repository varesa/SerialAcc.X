/*
 $License:
    Copyright (C) 2010 InvenSense Corporation, All Rights Reserved.
 $
 */
/******************************************************************************
 * $Id: log_at32.c $ 
 ******************************************************************************/
 
/**
 * @defgroup MPL_LOG
 * @brief Logging facility for the MPL
 *
 * @{
 *      @file     log_at32.c
 *      @brief    Core logging facility functions.
 *
 *
**/

#include <stdio.h>
#include <string.h>
#include <p32xxxx.h>

#include "packet.h"

#include "mltypes.h"

#include "log.h"
#include "../msg_buffer.h"

#define LOG_BUFFER_SIZE (256)

#ifdef WIN32
#define snprintf    _snprintf
#define vsnprintf   _vsnprintf
#endif

int _MLPrintLog (int priority, const char* tag, const char* fmt, ...)
{
    va_list ap;
    int result;

    va_start(ap, fmt);
    result = _MLPrintVaLog(priority,tag,fmt,ap);
    va_end(ap);

    return result;
}

int _MLPrintVaLog(int priority, const char* tag, const char* fmt, va_list args)
{
    int result;
    char buf[LOG_BUFFER_SIZE];
    char new_fmt[LOG_BUFFER_SIZE];
    char priority_char;

    if (NULL == fmt) {
        fmt = "";
    }

    switch (priority) {
    case MPL_LOG_UNKNOWN:
        priority_char = 'U';
        break;
    case MPL_LOG_VERBOSE:
        priority_char = 'V';
        break;
    case MPL_LOG_DEBUG:
        priority_char = 'D';
        break;
    case MPL_LOG_INFO:
        priority_char = 'I';
        break;
    case MPL_LOG_WARN:
        priority_char = 'W';
        break;
    case MPL_LOG_ERROR:
        priority_char = 'E';
        break;
    case MPL_LOG_SILENT:
        priority_char = 'S';
        break;
    case MPL_LOG_DEFAULT:
    default:
        priority_char = 'D';
        break;
    };

    result = snprintf(new_fmt, sizeof(new_fmt), "%c/%s:%s", 
                       priority_char, tag, fmt);
    if (result <= 0) {
        return INV_ERROR_LOG_MEMORY_ERROR;
    }
    result = vsnprintf(buf,sizeof(buf),new_fmt, args);
    if (result <= 0) {
        return INV_ERROR_LOG_OUTPUT_ERROR;
    }
    
    result = _MLWriteLog(buf, strlen(buf));
    return INV_SUCCESS;
}

static int debugSendPacket (const char * msg, int len)
{
    unsigned char out[100];
    int ii;
	
	// Copy, adding padding if this is the end
    for (ii = 0; ii < 100; ii++)
		out[ii] = (ii < len)? msg[ii] : 0;
		
	Nop();
	Nop();
	Nop();
	Nop();

	ii = 0;
	while((out[ii] != 0) & (ii < 100))
	{
		/*while(U2STAbits.UTXBF == 1);    	//  Wait for transmit buffer to be empty
		U2TXREG = out[ii];				//  Load transmit buffer with data.*/
		ii++;
	}
//	sendPacket(PACKET_TYPE_DEBUG,out);    commented out by Stephen Allen 8/12/11

//    if (len > 10)
//        debugSendPacket(&msg[10], len-10);

    return len;
}



int _MLWriteLog (const char * buf, int buflen)
{
    return debugSendPacket(buf,buflen);
}



/**
 * @}
**/


