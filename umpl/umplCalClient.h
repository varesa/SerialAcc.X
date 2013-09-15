/*
 $License:
    Copyright (C) 2011 InvenSense Corporation, All Rights Reserved.
 $
 */

#ifndef __UMPL_CAL_CLIENT_H__
#define __UMPL_CAL_CLIENT_H__

#include "mltypes.h"

/* Interface with host PC */
inv_error_t umplFetchCalibration(void);
inv_error_t umplSendCal(unsigned char *cal, unsigned int len);

/* Interface to fetched data */
int getCalibrationLen(void);
bool calDataAvailable(void);
void getCalibrationData(unsigned char *cal, unsigned int  len);
void printCalData(void);
#endif /* __UMPL_CAL_CLIENT_H__ */
