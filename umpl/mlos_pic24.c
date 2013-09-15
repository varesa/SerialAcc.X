/*
 * Copyright � 2007-2010 Microchip Technology Inc.  All rights reserved.
 *
 *
 * You may use this software, and any derivatives, exclusively with Microchip�s products. 
 * Microchip and its licensors retain all ownership and intellectual property rights in 
 * the accompanying software and in all derivatives hereto.  This software and any 
 * accompanying information is for suggestion only.  It does not modify Microchip�s 
 * standard warranty for its products.  You agree that you are solely responsible for 
 * testing the software and determining its suitability.  Microchip has no obligation 
 * to modify, test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, 
 * IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE, ITS 
 * INTERACTION WITH MICROCHIP�S PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN 
 * ANY APPLICATION. 
 *
 * IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT 
 * (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, 
 * CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL 
 * OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO 
 * THE SOFTWARE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY 
 * OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S 
 * TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE 
 * AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS.
 *


 $License:
    Copyright (C) 2010 InvenSense Corporation, All Rights Reserved.
 $
 
*******************************************************************************
 *
 * $Id: mlos_win32.c 4598 2011-01-25 19:33:13Z prao $
 *
 ******************************************************************************

 *
 *  @defgroup MLOS
 *  @brief OS Interface for Atmel AVR32
 *
 *  @{
 *      @file mlos.c
 *      @brief OS Interface.
 */

/* ------------- */
/* - Includes. - */
/* ------------- */

#include "mlos.h"
#include "stdint_invensense.h"
//#include <asf.h>

#include "log.h"

/* -------------- */
/* - Functions. - */
/* -------------- */


/**
 *  @brief  Allocate space.
 *  @param  numBytes  
 *              number of bytes.
 *  @return pointer to allocated space.
 */
void *inv_malloc(unsigned int numBytes)
{
    MPL_LOGE("inv_malloc should not be used!\n");
    return NULL;
}


/**
 *  @brief  Free allocated space.
 *  @param  ptr pointer to space to deallocate
 *  @return error code.
 */
inv_error_t inv_free(void *ptr)
{
    MPL_LOGE("inv_free should not be used!\n");
    return INV_SUCCESS;
}





/**
 *  @brief  open file
 *  @param  filename    name of the file to open.
 *  @return error code.
 */
FILE *inv_fopen(char *filename)
{
    MPL_LOGE("inv_fopen should not be used!\n");
    return NULL;
}


/**
 *  @brief  close the file.
 *  @param  fp  handle to file to close.
 *  @return error code.
 */
void inv_fclose(FILE *fp)
{
    MPL_LOGE("inv_fclose should not be used!\n");
    return;
}


/**
 *  @brief  Sleep function.
**/
void inv_sleep(int mSecs)
{
long tickCountOnEntry;
	/*// interrupt actually occurs 8 times per millisecond
	mSecs = mSecs * 8;

	tickCountOnEntry = tickCount;					// store starting value
	while(tickCount < tickCountOnEntry + mSecs);	// wait for time to pass*/
    DelayMs(8);
}


/**
 *  @brief  get system's internal tick count.
 *          Used for time reference.
 *  @return current tick count.
**/
unsigned long inv_get_tick_count(void)
{
        return 1; // @todo: Implement the tick counter
	//return tickCount;
}

/**
 *
 * MUTEX Stubs
 *
**/
inv_error_t inv_create_mutex(HANDLE *mutex) 
{
    return INV_SUCCESS;
}

inv_error_t inv_lock_mutex(HANDLE mutex)
{
    return INV_SUCCESS;
}

inv_error_t inv_unlock_mutex(HANDLE mutex)
{
    return INV_SUCCESS;
}

inv_error_t inv_destroy_mutex(HANDLE handle)
{
    return INV_SUCCESS;
}

  /**********************/
 /** @} */ /* defgroup */
/**********************/


