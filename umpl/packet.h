/*
 $License:
    Copyright (C) 2011 InvenSense Corporation, All Rights Reserved.
 $
 */

#ifndef __PACKET_H__
#define __PACKET_H__

#define PACKET_TYPE_DEBUG       (1)
#define PACKET_TYPE_QUATERNION  (2)

#define PACKET_TYPE_CALIB_REQ   (3)
#define PACKET_TYPE_CALIB_START (4)
#define PACKET_TYPE_CALIB_DATA  (5)
#define PACKET_TYPE_CALIB_STOP  (6)


int sendPacket(unsigned char type, unsigned char * payload);
int getPacket(unsigned char *type, unsigned char * payload);

#endif /* __PACKET_H__ */
