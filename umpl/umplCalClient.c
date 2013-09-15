/*
 $License:
    Copyright (C) 2010 InvenSense Corporation, All Rights Reserved.
 $
 */
/******************************************************************************
 *
 * $Id: umplCalibClient.c 4/14/2011 10:17:57 AM  sgurumani $
 *
 * Created: 4/14/2011 10:17:57 AM
 *  Author: sgurumani
 */ 

/** 
 *  @defgroup UMPL-CALIB
 *  @brief  uMPL Calibration Implementation.
 *          umplCalibClient.c provides a mechanism to store and load calibration data
 *			on host PC. This implementation may be used when there is no provision to 
 *			store on internal/external flash.
 *
 *  @{
 *      @file   umplCalibClient.c
 *      @brief  Implements Load/Store Calibration on host PC. 
 *				This module uses a data client to send calibration data or request for calibration
 *				data to a listening daemon. 
 *				
**/

/* ------------------ */
/* - Include Files. - */
/* ------------------ */
#include <stdio.h>
#include <string.h>
#include "asf.h"
#include "log.h"
#undef MPL_LOG_TAG
#define MPL_LOG_TAG "uMPL-cal"
#include "umplCalClient.h"
#include "packet.h"
#include "mlos.h"
#include "checksum.h"
// #include "ml_stored_data.h"
#define INV_CAL_CHK_LEN (4)
#define INV_CAL_HDR_LEN (6)

static bool calDataFlag = false;
/* calBuffer must be be a multiple of 10 in size so we can
 * write whole packets (len 10) without checking bounds. */
static unsigned char calBuffer[2800];
static int calLength = 0;


void doCheckSum(void)
{
	int len = 0;
	int calType = 0;
	uint32_t chk = 0;
    uint32_t cmp_chk = 0;
	int ptr;
	
	len = 0;
    len += 16777216L * ((int)calBuffer[0]);
    len += 65536L    * ((int)calBuffer[1]);
    len += 256       * ((int)calBuffer[2]);
    len +=              (int)calBuffer[3];
	calType = ((int)calBuffer[4]) * 256 + ((int)calBuffer[5]);
    if (calType > 5) {
        MPL_LOGE("Unsupported calibration file format %d. "
                 "Valid types 0..5\n", calType);      
    }
	 /* check the checksum */
    chk = 0;
    ptr = len - INV_CAL_CHK_LEN;

    chk += 16777216L * ((uint32_t)calBuffer[ptr++]);
    chk += 65536L    * ((uint32_t)calBuffer[ptr++]);
    chk += 256       * ((uint32_t)calBuffer[ptr++]);
    chk +=              (uint32_t)calBuffer[ptr++];
	
    cmp_chk = inv_checksum(calBuffer + INV_CAL_HDR_LEN, 
        len - (INV_CAL_HDR_LEN + INV_CAL_CHK_LEN));
         
    if(chk != cmp_chk) {
         MPL_LOGE("CHECKSUM FAILED\n", cmp_chk);      
    }
}

/**
 *  @brief Sends a request to the daemon to retrieve and send calibration data stored on host PC. 
 *		   Once the data is successfully received, it is stored in a local Buffer.
 *
 *
 *  @return INV_SUCCESS if successful; a non-zero error code otherwise.
 */

inv_error_t umplFetchCalibration(void)
{
	int result;
	unsigned char id;
	unsigned char payload[10];
	int len, ii, jj;
	
	// Initiate transaction with CALIB_REQ
	result = sendPacket(PACKET_TYPE_CALIB_REQ, payload);
	if (result != 0)
		return INV_ERROR;
	
	// Read length from host in the START packet
	result = getPacket(&id, payload);
	if (result != 0) {
		return INV_ERROR;
	}		
	if (id == PACKET_TYPE_CALIB_STOP){
		payload[0] = 0; payload[1] = 0;
		sendPacket(PACKET_TYPE_CALIB_STOP,payload);
		return INV_ERROR;
	}
	if (id != PACKET_TYPE_CALIB_START)
		return INV_ERROR;
	len = payload[0] * 256 + payload[1];

	if (len > 2800) {
		payload[0] = 254; payload[1] = 254; // Host error code
		sendPacket(PACKET_TYPE_CALIB_STOP,payload);
		return INV_ERROR;
	}
	
	// Invalidate buffer until we exit successfully.
	calDataFlag = FALSE;

	// cal data is broken into chunks of 10 bytes
	for (ii = 0; ii < len; ii += 10)
	{
		// Get next packet
		result = getPacket(&id,payload);
		if (result != 0 || id != PACKET_TYPE_CALIB_DATA){
			payload[0] = 255; payload[1] = 255; // Host error code	
			sendPacket(PACKET_TYPE_CALIB_STOP, payload);
			return INV_ERROR;
		}
		// Copy payload to buffer
		for (jj = 0; jj < 10; jj++)
			calBuffer[ii+jj] = payload[jj];
	}
	
	payload[0] = 0; payload[1] = 0; // Host success code
	result = sendPacket(PACKET_TYPE_CALIB_STOP,payload);
	if (result != 0)
		return INV_ERROR;
	
	calDataFlag = TRUE;
	calLength = len;
	//MPL_LOGI("umplFetchCalibration successfully got %d bytes\n",calLength);
	
	
	doCheckSum();
	return INV_SUCCESS;
}

/**
 *  @brief  This function is called by umplSendCal to send a INIT packet to the daemon 
 *			to indicate that the data client is ready to start sending calibration data. 
 *
 *
 *  @return INV_SUCCESS if successful; a non-zero error code otherwise.
 */
static inv_error_t umplSendCalInitPacket(unsigned int caliblen)
{
	unsigned char payload[10];
	int result;
	payload[0] = caliblen / 256;
	payload[1] = caliblen % 256;
	result = sendPacket(PACKET_TYPE_CALIB_START,payload);
	if (result != 0)
		return INV_ERROR;
	return INV_SUCCESS;
}

/**
 *  @brief  This function is called by umplSendCal to send the actual calibration data
 *			to the daemon to be stored on host PC.
 *
 *
 *  @return INV_SUCCESS if successful; a non-zero error code otherwise.
 */
static inv_error_t umplSendCalData(unsigned char *cal, unsigned int len)
{
	inv_error_t result = INV_SUCCESS;
	unsigned char payload[10];
	int startidx, ii, r;
	for (startidx = 0; startidx < len; startidx += 10) {
		for (ii = 0; ii < 10; ii++) {
			payload[ii] = (startidx+ii < len) ? cal[startidx+ii] : 0;
		}
		r = sendPacket(PACKET_TYPE_CALIB_DATA, payload);
		if (r != 0)
			return INV_ERROR;
	}	
	return INV_SUCCESS;
}

/**
 *  @brief  This function is called by umplSendCal to send a STOP packet to the daemon 
 *			to indicate that the data client has finished sending calibration data. 
 *
 *
 *  @return INV_SUCCESS if successful; a non-zero error code otherwise.
 */
static inv_error_t umplSendCalStopPacket(void)
{
	int result;
	unsigned char payload[10]; // no significance
	result = sendPacket(PACKET_TYPE_CALIB_STOP, payload);
	if (result != 0)
		return INV_ERROR;
	return INV_SUCCESS;
}

/**
 *  @brief  sends the calib data to PC to be stored to file. This function is called by inv_serial_write_cal,
 *			which is in turn called by inv_store_calibration to store the calibration data.
 *			An INIT packet is first sent to the daemon followed by the actual calibration data. 
 *			A STOP packet indicates the end of data.
 *
 *  @param  cal
 *             A pointer to calibration data.
 *  @param  len
 *             Length of the calibration data.
 *  @return INV_SUCCESS if successful; a non-zero error code otherwise.
 */
inv_error_t umplSendCal(unsigned char *cal, unsigned int len)
{
	inv_error_t resultInit, resultSend, resultStop;
	/* Updating the local calBuffer */
	memcpy(calBuffer, cal, len);
	resultInit = umplSendCalInitPacket(len);
	if (resultInit != INV_SUCCESS)
		return INV_ERROR_CALIBRATION_STORE;
	
	resultSend = umplSendCalData(cal, len);
	/* regardless of resultSend, send a stop packet */
	resultStop = umplSendCalStopPacket();
	if (resultSend != INV_SUCCESS || resultStop != INV_SUCCESS)
		return INV_ERROR_CALIBRATION_STORE;
	
}

/**
 *  @brief  calDataAvailable is used to check if calibration data is available
 *		    in local buffer.
 *
 *  @return TRUE if calibration data is available; FALSE otherwise.
 */
bool calDataAvailable(void)
{
	return calDataFlag;
}

/**
 *  @brief  returns the length of the calibration data stored locally in calBuffer. This function is called
 *			by inv_serial_get_cal_length. 
 *
 *  @return Length of calibration data.
 */
int getCalibrationLen(void)
{
	return (calDataFlag > 0) ? calLength : 0;	
}

/**
 *  @brief  returns the calibration data stored locally in calBuffer. This function is called by 
 *			inv_serial_read_cal() which is in turn called by inv_load_calibration to load the stored calibration data.
 *
 *  @param  cal
 *             A pointer to calibration data.
 *  @param  len
 *             Length of the calibration data.
 */
void getCalibrationData(unsigned char *cal, unsigned int  len)
{
	if (calDataFlag != 0)
		memcpy(cal, calBuffer, sizeof(calBuffer));
}

void printCalData(void)
{
	for(int i = 0; i< 200; i++)
	{
		MPL_LOGI("Relevant Cal data\n");
		MPL_LOGI("%d\n",calBuffer[i]);
	}
}
