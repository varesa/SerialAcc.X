#include <stdio.h>

#include "msg_buffer.h"

void appendBuffer(char* msg) {
    sprintf(msg_buffer, "%s%s", msg_buffer,msg);
    dataInBuffer = TRUE;
}