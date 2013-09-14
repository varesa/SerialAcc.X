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
#define MPU_ADDR 0x68
#define I2C_SPEED 400000

#define I2C_READ 1
#define I2C_WRITE 0

void MPU_init(void);
//TODO: MPU_getData();

#endif	/* I2C_MPU_H */

