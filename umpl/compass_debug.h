/*
 $License:
    Copyright (C) 2011 InvenSense Corporation, All Rights Reserved.
 $
 */

#ifndef __INV_COMPASS_DEBUG_H__
#define __INV_COMPASS_DEBUG_H__

#define PACKET_TYPE_RAWMAG_X (10)
#define PACKET_TYPE_RAWMAG_Y (11)
#define PACKET_TYPE_RAWMAG_Z (12)
#define PACKET_TYPE_BIAS_X   (13)
#define PACKET_TYPE_BIAS_Y   (14)
#define PACKET_TYPE_BIAS_Z   (15)

int debug_rawmag(long * raw);
int debug_bias(long * bias);

#endif // __INV_COMPASS_DEBUG_H__

