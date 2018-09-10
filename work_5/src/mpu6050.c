#include "mpu6050.h"
void mpu6050_init(){
	i2c_master_write_simple(MPU_ADDRESS,SLEEP_CONFIG,0);
	i2c_master_write_simple(MPU_ADDRESS,GYRO_CONFIG,0);
	i2c_master_write_simple(MPU_ADDRESS,SAMPLE_RATE,0);
}
u16 mpu6050_get_gyro_x(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,G_X_H);
}
u16 mpu6050_get_gyro_y(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,G_Y_H);
}
u16 mpu6050_get_gyro_z(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,G_Z_H);
}
u16 mpu6050_get_aaccel_x(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,A_X_H);
}
u16 mpu6050_get_aaccel_y(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,A_Y_H);
}
u16 mpu6050_get_accel_z(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,A_Z_H);
}
