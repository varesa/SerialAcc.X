/* 
 * File:   i2c_mpu.h
 * Author: esa
 *
 * Created on 14. syyskuuta 2013, 16:08
 */

#ifndef I2C_MPU_H
#define	I2C_MPU_H

#include "Microchip/GenericTypeDefs.h"

#define WRITE 0
#define READ 1

enum HWSTATE {
    IDLE,
    START,
    RESTART,
    TRANSMIT,
    STOP
};

enum STAGE {
    ADDRESS, 
    REGISTER,
    DATA
};

struct PACKAGE {
    unsigned char address;
    unsigned char reg;
    unsigned char *data;
    unsigned char length;
    unsigned char index;
    unsigned char direction;
};

int DATA_READY;
int ACTION_REQUIRED;



void I2C_init(void);

int i2c_write(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data);
int i2c_read(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data);

int get_ms(unsigned long *count);

void I2C_Tasks();

#endif	/* I2C_MPU_H */

