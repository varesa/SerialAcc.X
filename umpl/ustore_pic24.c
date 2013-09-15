
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
 */

/*
 $License:
    Copyright (C) 2011 InvenSense Corporation, All Rights Reserved.
 $
 */

/*******************************************************************************
 *
 * $Id:$
 *
 ******************************************************************************/

/*  ustore_stub_io.c
 *  This file implements the input and output for the "ustore" routines.
 *  It must implement the primitives found in ustore_delegate_io.h and
 *  ustore_manager_io.h.
 *
 *  This file is nonfunctional in its current state. These stubs will
 *  only work properly if the 
 *
 *  The ustore_manager, implemented in ustore_manager.c, will make calls
 *  found in ustore_manager_io.h to open and close the nonvolatile memory
 *  (sometimes abbreviated as nvmem) for loading and storing. The ustore
 *  delegates (these are the actual modules of code which are loading and
 *  storing data in nonvolatile memory) will make calls to the primitives
 *  found in ustore_delegate_io.h. 
 *
 *  Once you have read through the comments below and understand how to
 *  use this file, uncomment the line "#define USTORE_STUB_RETURN_ERROR"
 *  below to allow the project to compile. Calls to inv_uload_open and
 *  inv_ustore_open will return an error until this is removed, which 
 *  will prevent the ustore_manager from loading or storing calibration.
 * 
 *  (When you add a complete implementation to this file, eliminate the
 *  sections wrapped in USTORE_STUB_RETURN_ERROR macros below.)
 */

#define USTORE_STUB_RETURN_ERROR 

#define USTORE_STUB_SUPRESS_WARNING
#ifndef USTORE_STUB_SUPRESS_WARNING
#error ustore_stub_io.c is nonfunctional.
#error read the comments in ustore_stub_io.c to find out how to fix this.
#endif


#include <string.h>

#include <p32xxxx.h>
#include "ustore_pic24.h"

#include "ustore_manager.h"
#include "ustore_delegate_io.h"
#include "ustore_manager_io.h"
#include "mlsl.h"
#include "log.h"
#include "packet.h"
#undef MPL_LOG_TAG
#define MPL_LOG_TAG "MPL-ustore-mlsl-io"

#define USTORE_STATE_CLOSED      0
#define USTORE_STATE_STORE_OPEN  1
#define USTORE_STATE_LOAD_OPEN   2

#define STORE_CAL_SIZE 100

/* We track the store and load state with this
 * flag. This prevents overlapping store and load. 
 */
typedef int nvmem_addr_t;
static int state = USTORE_STATE_CLOSED;


int nvmem_write(int destination, int *source, int len)
{


unsigned long progAddr; 		// Address of row to erase
unsigned int offset;
unsigned int progDataL;
unsigned int progDataH = 0x00;
unsigned char i, byte0, byte1;

	/*//Set up pointer to the first memory location to be written
	//TBLPAG = progAddr>>16; 				// Initialize PM Page Boundary SFR
        // ^ PIC32 doesn't need pages?
	offset = progAddr & 0xFFFF; 		// Initialize lower word of address
	__builtin_tblwtl(offset, 0x0000); 	// Set base address of erase block

	// with dummy latch write

	NVMCON = 0x4042; // Initialize NVMCON
	//asm("DISI #5"); // Block all interrupts with priority <7
	// for next 5 instructions

	__builtin_write_NVM(); // check function to perform unlock
	// sequence and set WR


	for (i=0; i<len; i=i+2)
	{
		byte0 = &source+i;
		byte1 = &source+i+1;		
	
		progDataL = byte1 << 8;
		progDataL = progDataL | byte0;

		progAddr = 0x02A000 | (i/2); 				// Address of word to program

		//Set up NVMCON for word programming
		NVMCON = 0x4003; 					// Initialize NVMCON
	
		//Set up pointer to the first memory location to be written
		//TBLPAG = progAddr>>16; 				// Initialize PM Page Boundary SFR
                // ^ PIC32 doesn't need pages?
		offset = progAddr & 0xFFFF; 		// Initialize lower word of address
	
		//Perform TBLWT instructions to write latches
		__builtin_tblwtl(offset, progDataL); // Write to address low word
		__builtin_tblwth(offset, progDataH); // Write to upper byte

		//asm("DISI #5"); 		// Block interrupts with priority <7
								// for next 5 instructions
	
		__builtin_write_NVM(); // C30 function to perform unlock
		// sequence and set WR
	}*/

    return len;
}



int nvmem_read(int source, unsigned char *destination, int len)
{
	/*int i;

	//DSRPAG = 0x0205;			// Program memory range 0x020000 to 0x02FFFF maps to data space
        //Commented out, as this doesn't seem to do anything anyway /esa
//	W1 = 0x8000;				// point to start of program memory window.

	for(i == 0; i > len; i++)
	{
//		destination[i] = [W1];		// read from RAM address with bit 15 set.
	}*/
    return len;
}

/* TODO IMPLEMENTATION DETAILS
 * These stubs track the bounds of the calibration memory
 * with the predefined addresses cal_data and cal_end.
 * The state of the store or load is stored as addresses
 * pcal (as in, pointer to cal) and section_end. 
 * The stub code assumes the nvmem_addr_t has the properties
 * of a pointer or an offset in a buffer The storage space is
 * assumed to be uniform between cal_data and cal_end.
 */

/* Buffer used for store and load */
nvmem_addr_t cal_data = 0;
nvmem_addr_t cal_end;

/* ustore state */
nvmem_addr_t pcal;
nvmem_addr_t section_end;

/* --------- S E C T I O N - R O U T I N E S ------- */



inv_error_t inv_ustoreload_set_max_len(int l)
{
    if (state == USTORE_STATE_CLOSED)
        return INV_ERROR;

    if (pcal + l <= cal_end){
        section_end = pcal + l;
        return INV_SUCCESS;
    } else {
        return INV_ERROR_MEMORY_EXAUSTED;
    }
}

void inv_ustoreload_reset_len(void)
{
    section_end = 0;
}

/* ------------- S T O R E - R O U T I N E S ------- */

inv_error_t inv_ustore_open(void)
{
    inv_error_t result;
    if (state != USTORE_STATE_CLOSED)
        return INV_ERROR;
    pcal = cal_data;
    section_end = 0;
    cal_end = cal_data + STORE_CAL_SIZE;
    state = USTORE_STATE_STORE_OPEN;

    /* TODO INSERT IMPLEMENTATION HERE
     * You should do whatever is appropriate
     * to initialize nonvolatile memory for 
     * for storage. This may be a call to fopen,
     * powering up an external storage device,
     * unlocking a memory page, etc. etc.
     */
    
#ifdef USTORE_STUB_RETURN_ERROR
    /* Return error to prevent stub implementation from returning bad data. */
    return INV_ERROR;
#else
    return INV_SUCCESS;
#endif
}

inv_error_t inv_ustore_close(void)
{
    inv_error_t result = INV_SUCCESS;
    if (state != USTORE_STATE_STORE_OPEN)
        return INV_ERROR;
    section_end = NULL;
    cal_end = NULL;
    state = USTORE_STATE_CLOSED;

    /* TODO INSERT IMPLEMENTATION HERE
     * This function is called after calls
     * to ustore are complete. Finalize any
     * writes at this time.
     */

    return result;
}

/* TODO IMPLEMENTATION CHOICE AVAILABLE HERE
 * inv_ustore_byte and inv_ustore_mem may be implemented
 * in terms of the other, i.e. inv_ustore_mem is a loop on
 * inv_ustore_byte, or inv_ustore_byte is a call to
 * inv_ustore_mem with length 1.
 * You can implement whichever of these makes more sense
 * for your platform.
 */
inv_error_t inv_ustore_byte(unsigned char b)
{
    return inv_ustore_mem((const void *)&b, 1);
}

inv_error_t inv_ustore_mem(const void *b, int length)
{
    if (state != USTORE_STATE_STORE_OPEN)
        return INV_ERROR;
    if (section_end != NULL && 
        (pcal + length) > section_end)
        return INV_ERROR_MEMORY_EXAUSTED;

    if (pcal + length >= cal_end)
        return INV_ERROR_MEMORY_EXAUSTED;

    nvmem_write(pcal,  b, (size_t)length);
    pcal += length;
    return INV_SUCCESS;
}

/* ------------- L O A D - R O U T I N E S ------- */

inv_error_t inv_uload_open(void)
{
    inv_error_t result;
    unsigned int store_length;
    unsigned char dataLen[4];
    if (state != USTORE_STATE_CLOSED)
        return INV_ERROR;
    
    /* TODO INSERT IMPLEMENTATION HERE
     * Along the same lines as inv_ustore_open, except this time
     * prepare the nonvolatile memory for reading.
     * Prepare pcal to point to beginning of memory space.
     */ 

    pcal = cal_data;
    cal_end = cal_data + STORE_CAL_SIZE;
    section_end = 0;
    state = USTORE_STATE_LOAD_OPEN;

#ifdef USTORE_STUB_RETURN_ERROR
    /* Return error to prevent stub implementation from returning bad data. */
    return INV_ERROR;
#else
    return INV_SUCCESS;
#endif
}

inv_error_t inv_uload_close(void)
{
    if (state != USTORE_STATE_LOAD_OPEN)
        return INV_ERROR;
    
    /* TODO INSERT IMPLEMENTATION HERE
     * Along the same lines as inv_ustore_close, except
     * this time close the memory from reading.
     */
    
    section_end = NULL;
    cal_end = NULL;
    state = USTORE_STATE_CLOSED;
    return INV_SUCCESS;
}

/* TODO IMPLEMENTATION CHOICE AVAILABLE HERE
 * inv_ustore_byte and inv_ustore_mem may be implemented
 * in terms of the other, i.e. inv_ustore_mem is a loop on
 * inv_ustore_byte, or inv_ustore_byte is a call to
 * inv_ustore_mem with length 1.
 * You can implement whichever of these makes more sense
 * for your platform.
 */
inv_error_t inv_uload_byte(unsigned char *b)
{
    return inv_uload_mem(b, 1);
}

inv_error_t inv_uload_mem(void *b, int length)
{
    if (state != USTORE_STATE_LOAD_OPEN)
        return INV_ERROR;
    if (section_end != NULL &&
    (pcal + length) > section_end)
        return INV_ERROR_MEMORY_EXAUSTED;
    if (pcal + length >= cal_end)
        return INV_ERROR_MEMORY_EXAUSTED;

    nvmem_read(pcal, b, length);
    pcal += length;
    return INV_SUCCESS;
}

///*  TODO REPLACE IMPLEMENTATION HERE
// *  This implementation just overwrites the existing
// *  file with zeroes, which should be sufficient to make
// *  the ustore_manager reject the heading tags at the beginning
// *  of each stored section.
// *  If you are using a filesystem for nvmem, you may want to
// *  delete the storage file here. If you are checking some sort 
// *  of flag on calls to inv_uload_open, you may want to clear it
// *  here.
// */
//
//inv_error_t inv_clear_nvmem(void)
//{
//    int i;
//    const char zero = 0;
//	unsigned char result;
//
//    result = inv_ustore_open();
//    if (result != INV_SUCCESS){
//        LOG_RESULT_LOCATION(result);
//        return result;
//    }
//    for (i = 0; i < STORE_CAL_SIZE; i++) {
//        result = inv_ustore_mem(NULL, 0x00, sizeof(char));
//        if (result != INV_SUCCESS) {
//            LOG_RESULT_LOCATION(result);
//            return result;
//        }
//    }
//    result = inv_ustore_close();
//    if (result != INV_SUCCESS) {
//        LOG_RESULT_LOCATION(result);
//        return result;
//    }
//    return INV_SUCCESS;
//}



