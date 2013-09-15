/* 
 * File:   i2c_mpu.h
 * Author: esa
 *
 * Created on 14. syyskuuta 2013, 16:08
 */

#ifndef I2C_MPU_H
#define	I2C_MPU_H

#include "Microchip/GenericTypeDefs.h"

#define I2C_DEV I2C2
#define I2C_SPEED 400000


void I2C_init(void);
int i2c_write(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data);
int i2c_read(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data);
int get_ms(unsigned long *count);


#endif	/* I2C_MPU_H */

