#ifndef __MPU_9250
#define __MPU_9250

#include "math.h"
#include "i2c.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"

#define MPU9150_MAGNO_ADDRESS 0x18//0x48
#define MPU9150_MAGNO_CNTRL 0x0A
#define MPU9150_ADDRESS 0xD0
#define MPU9150_WHO_AM 0x75
#define MPU9150_GYRO_CONFIG 0x1B
#define MPU9150_SLEEP_CONFIG 0x6B
#define MPU9150_SAMPLE_RATE 0x19
#define MPU9150_USER_CONTROL 0x6A
#define MPU9150_INT_PIN_CFG 0x37


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

#define M_X_L 0x03
#define M_X_H 0x04
#define M_Y_L 0x05
#define M_Y_H 0x06
#define M_Z_L 0x07
#define M_Z_H 0x08

#define GRYRO_SCALE 131
#define TIME	0.0001	 				//base on ur timer clock 10khz
#define LOOP_COUNT 256					//top of counter


#define FIRST_NAGATIVE_X_NUM 259
#define FIRST_NAGATIVE_Y_NUM 259

#define min_x (-370+FIRST_NAGATIVE_X_NUM)
#define min_y (-384+FIRST_NAGATIVE_Y_NUM)
#define min_z -384
#define max_x 79 //112
#define max_y 52 //96
#define max_z 89 //85


int 	mpu9150_get_accel_z();
int 	mpu9150_get_accel_x();
int 	mpu9150_get_accel_y();

int 	mpu9150_get_gyro_z();
int 	mpu9150_get_gyro_y();
int 	mpu9150_get_gyro_x();

char 	mpu9150_get_name();
void 	mpu9150_init();
void 	mpu9150_calibrate(int *OFFSET_X,int *OFFSET_Y,int *OFFSET_Z);
float 	mpu9150_make_zero_degree(int zero,int degree);
void mpu9150_fuse_data(int OFF_X,int OFF_Y,int OFF_Z,int *f_x,int *f_y,int *f_z);
void mpu9150_degree_mag(int * _angle_x,int * _angle_y);
void show_mpu();

int mpu9150_get_mag_x();
int mpu9150_get_mag_y();
int mpu9150_get_mag_z();






#endif
