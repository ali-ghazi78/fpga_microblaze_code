/*
 * mpu6050.h
 *
 *  Created on: Aug 14, 2018
 *      Author: ali
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "i2c.h"
#include "math.h"

#define MPU_ADDRESS 0xD0
#define MPU_WHO_AM 0x75
#define GYRO_CONFIG 0x1B
#define SLEEP_CONFIG 0x6B
#define SAMPLE_RATE 0x19
#define USER_CONTROL 0x6A

#define G_X_H 0x43
#define G_X_L 0x44
#define G_Y_H 0x45
#define G_Y_L 0x46
#define G_Z_H 0x47
#define G_Z_L 0x48

#define A_X_H 0x3B
#define A_X_L 0x3C
#define A_Y_H 0x3D
#define A_Y_L 0x3E
#define A_Z_H 0x3F
#define A_Z_L 0x40

float deg_accel_z_2,deg_accel_x_2,deg_accel_y_2;
float g_x,g_y,g_z;
float a_x,a_y,a_z;
float degree_x,degree_y,degree_z;
float fused_x,fused_y,fused_z;

u16 mpu6050_get_accel_z();
u16 mpu6050_get_accel_x();
u16 mpu6050_get_accel_y();

u16 mpu6050_get_gyro_z();
u16 mpu6050_get_gyro_y();
u16 mpu6050_get_gyro_x();

u8 mpu6050_get_name();

void mpu6050_init();
void mpu_calibrate(int *OFFSET_X,int *OFFSET_Y,int *OFFSET_Z);
void exception(unsigned char *string,float number,int div);



void mpu_fuse_data(int OFF_X,int OFF_Y,int OFF_Z);


#endif /* MPU6050_H_ */
