/* 
 * File:   msg_buffer.h
 * Author: esa
 *
 * Created on 14. syyskuuta 2013, 16:36
 */

#ifndef MSG_BUFFER_H
#define	MSG_BUFFER_H

#include "Microchip/GenericTypeDefs.h"

char msg_buffer[256];
BOOL dataInBuffer;
void appendBuffer(char* msg);

#endif	/* MSG_BUFFER_H */

