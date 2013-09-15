#include <stdio.h>

#include "msg_buffer.h"

void appendBuffer(char* msg) {
    sprintf(msg_buffer, "%s%s", msg_buffer,msg);
    dataInBuffer = TRUE;
}

void usbPrintf(const char* format, ...) {
    char dest[512];
    va_list args;
    va_start(args, format);
    vsprintf(dest, format, args);
    va_end(args);

    appendBuffer(dest);

}