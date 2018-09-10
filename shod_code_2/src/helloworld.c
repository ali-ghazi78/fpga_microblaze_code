/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include "my_lib/delay.h"
#include "my_lib/led.h"
#include "my_lib/my_intc.h"
#include "my_lib/i2c.h"
//#include "my_lib/mpu6050.h"
#include "my_lib/usart.h"
#include "my_lib/timer.h"





#define GRYRO_SCALE 131
#define TIME	0.0001	 				//base on ur timer clock 10khz


int counter_mpu;
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

int mpu6050_get_accel_z();
 int  mpu6050_get_accel_x();
int mpu6050_get_accel_y();

int mpu6050_get_gyro_z();
int mpu6050_get_gyro_y();
int mpu6050_get_gyro_x();

char mpu6050_get_name();

void mpu6050_init();
void mpu_calibrate(int *OFFSET_X,int *OFFSET_Y,int *OFFSET_Z);
void exception(unsigned char *string,float number,int div);



void mpu_fuse_data(int OFF_X,int OFF_Y,int OFF_Z);

int main(void)
{

	int OF_X,OF_Y,OF_Z;
	mpu6050_init();
	mpu_calibrate(&OF_X,&OF_Y,&OF_Z);

	my_putstr("salam\n");
	turn_led(1);
	delay_ms(1000);
	IntcLowLevelExample(INTC_BASEADDR);

	timer_set_up(5000,256);
	while(1){

		mpu_fuse_data(OF_X,OF_Y,OF_Z);
		my_put_int(g_x);
		my_putchar('\n');
		delay_ms(10);
	}
	return 0;

}















void mpu6050_init(){
	i2c_master_write_simple(MPU_ADDRESS,SLEEP_CONFIG,0);
	i2c_master_write_simple(MPU_ADDRESS,GYRO_CONFIG,0);
	i2c_master_write_simple(MPU_ADDRESS,SAMPLE_RATE,0);
}
char mpu6050_get_name(){
	return i2c_master_read_simple_1Byte(MPU_ADDRESS,MPU_WHO_AM);
}
int mpu6050_get_gyro_x(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,G_X_H);
}
int mpu6050_get_gyro_y(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,G_Y_H);
}
int mpu6050_get_gyro_z(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,G_Z_H);
}
signed int  mpu6050_get_accel_x(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,A_X_H);
}
int mpu6050_get_accel_y(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,A_Y_H);
}
int mpu6050_get_accel_z(){
	return i2c_master_read_simple_2Byte(MPU_ADDRESS,A_Z_H);
}
//-------------------------------------------------

float make_zero_degree(int zero,int degree)
{
    float x_2;
    if(degree>zero)
   {
		x_2=degree-zero;
   }
   else
   {
	   x_2=360-(zero-degree);
   }
    return x_2;

}
void mpu_fuse_data(int OFF_X,int OFF_Y,int OFF_Z)
{

	int t_x,t_y,t_z;
	float CO_A=.98;
	float CO_B=.02;
//	float deg_accel_z_2,deg_accel_x_2,deg_accel_y_2;
//	static float g_x,g_y,g_z;
//	static float a_x,a_y,a_z;
//	static float degree_x,degree_y,degree_z;
//	static float fused_x,fused_y,fused_z;

	int p_x,p_y,p_z;
	t_x=g_x;
	t_y=g_y;
	t_z=g_z;

	p_x=a_x;
	p_y=a_y;
	p_z=a_z;

	g_x=(float)mpu6050_get_gyro_x()-OFF_X;
	g_y=(float)mpu6050_get_gyro_y()-OFF_Y;
	g_z=(float)mpu6050_get_gyro_z()-OFF_Z;

	a_x=mpu6050_get_accel_x();
	a_y=mpu6050_get_accel_y();
	a_z=mpu6050_get_accel_z();

	g_x=(int)g_x/GRYRO_SCALE;
	g_y=(int)g_y/GRYRO_SCALE;
	g_z=(int)g_z/GRYRO_SCALE;

	g_x=t_x*.3+g_x*.7;
	g_y=t_y*.3+g_y*.7;
	g_z=t_z*.3+g_z*.7;

	a_x/=100;
	a_y/=100;//because of avr variable size i destroyed my precision
	a_z/=100;

	a_x=a_x*.4+p_x*.6;
	a_y=a_y*.4+p_y*.6;
	a_z=a_z*.4+p_z*.6;
	if((a_x==0&&a_y==0))
		deg_accel_z_2=0;
	else
		deg_accel_z_2= atan2(a_y,a_x)*180/M_PI; //xy plane

	if((a_y==0&&a_z==0))
		deg_accel_x_2=0;
	else
		deg_accel_x_2= atan2(a_y,a_z)*180/M_PI;//yz plane

	if((a_x==0&&a_z==0))
		deg_accel_y_2=0;
	else
		deg_accel_y_2= atan2(a_x,a_z)*180/M_PI;//zx plane

	deg_accel_x_2=(deg_accel_x_2>0)?deg_accel_x_2:360+deg_accel_x_2;
	deg_accel_y_2=(deg_accel_y_2>0)?deg_accel_y_2:360+deg_accel_y_2;
	deg_accel_z_2=(deg_accel_z_2>0)?deg_accel_z_2:360+deg_accel_z_2;
	deg_accel_y_2=360-deg_accel_y_2;
	deg_accel_z_2=360-deg_accel_z_2;


	timer_off();
	//////////x
	if(fused_x>deg_accel_x_2)
	{
		if((fused_x-deg_accel_x_2)>180)
			fused_x=deg_accel_x_2;
		else
			fused_x=(((float)g_x*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME)+fused_x)*CO_A+deg_accel_x_2*CO_B;
	}
	else if(fused_x<deg_accel_x_2)
	{
		if((deg_accel_x_2-fused_x)>180)
			fused_x=deg_accel_x_2;
		else
			fused_x=(((float)g_x*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME)+fused_x)*CO_A+deg_accel_x_2*CO_B;

	}
	//////////y

	if(fused_y>deg_accel_y_2)
	{
		if((fused_y-deg_accel_y_2)>180)
			fused_y=deg_accel_y_2;
		else
			fused_y=(((float)g_y*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME)+fused_y)*CO_A+deg_accel_y_2*CO_B;
	}
	else if(fused_y<deg_accel_y_2)
	{
		if((deg_accel_y_2-fused_y)>180)
			fused_y=deg_accel_y_2;
		else
			fused_y=(((float)g_y*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME)+fused_y)*CO_A+deg_accel_y_2*CO_B;
	}
	//////////z

	if(fused_z>deg_accel_z_2)
	{
		if((fused_z-deg_accel_z_2)>180)
			fused_z=deg_accel_z_2;
		else
			fused_z=(((float)g_z*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME)+fused_z)*CO_A+deg_accel_z_2*CO_B;
	}
	else if(fused_z<deg_accel_z_2)
	{
		if((deg_accel_z_2-fused_z)>180)
			fused_z=deg_accel_z_2;
		else
			fused_z=(((float)g_z*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME)+fused_z)*CO_A+deg_accel_z_2*CO_B;
	}

	//
	//    fused_y=(((float)g_y*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME)+fused_y)*.98+deg_accel_y_2*.02;
	//    fused_z=(((float)g_z*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME)+fused_z)*.98+deg_accel_z_2*.02;


	degree_x+=((float)g_x*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME);
	degree_y+=((float)g_y*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME);
	degree_z+=((float)g_z*(float)((long)counter_mpu*256+(timer_currenct_counter()))*(float)TIME);

	counter_mpu=0;
	timer_set_up(5000,256);
	timer_on();
	while((fused_x>360)||(fused_y>360))
	{
		if(fused_x>360){
			exception("fused_x",fused_x,0);
			my_putchar('c');
			fused_x=fused_x-360;
		}
		if(fused_y>360){
			my_putchar('d');
			fused_y=fused_y-360;
		}
		if(fused_z>360){
			my_putchar('d');
			fused_z=fused_z-360;
		}
	}
	while((fused_x<0)||(fused_y<0)||(fused_z<0))
	{
		if(fused_x<0)
			fused_x=360+fused_x;
		if(fused_y<0)
			fused_y=360+fused_y;
		if(fused_z<0)
			fused_z=360+fused_z;
	}
	while((degree_x>360)||(degree_y>360)||(degree_z>360))
	{
		if(degree_x>360)
			degree_x=degree_x-360;
		if(degree_y>360)
			degree_y=degree_y-360;
		if(degree_z>360)
			degree_z=degree_z-360;
	}
	while((degree_x<0)||(degree_z<0)||(degree_y<0))
	{
		if(degree_x<0)
			degree_x=360+degree_x;
		if(degree_y<0)
			degree_y=360+degree_y;
		if(degree_z<0)
			degree_z=360+degree_z;
		//exception("leve",5,0);
	}
}










void mpu_calibrate(int *OFFSET_X,int *OFFSET_Y,int *OFFSET_Z)
{
	int i=0;

    my_putstr("\n----------start_calibratin-------\n");

    for(;i<500;i++)
    {
           *OFFSET_X=(float)mpu6050_get_gyro_x();
           *OFFSET_Y=(float)mpu6050_get_gyro_y();
           *OFFSET_Z=(float)mpu6050_get_gyro_z();
    }
    i=0;
    for(;i<50;i++)
    {
           *OFFSET_X+=mpu6050_get_gyro_x();
           *OFFSET_Y+=mpu6050_get_gyro_y();
           *OFFSET_Z+=mpu6050_get_gyro_z();
    }
    *OFFSET_X/=50;
    *OFFSET_Y/=50;
    *OFFSET_Z/=50;

    exception("G_x_OFFSET",*OFFSET_X,0);
    exception("G_y_OFFSET",*OFFSET_Y,0);
    exception("G_z_OFFSET",*OFFSET_Z,0);

    delay_ms(1000);
    my_putstr("\n----------finish_calibratin-------\n");
}
void exception(unsigned char *string,float number,int div)
{

        my_putstr("\n");
        my_putstr(string);
        my_putstr("{");
        my_put_int(number);
        my_putstr("}\n");
}

