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
#include "my_lib/mpu9150.h"
#include "my_lib/usart.h"
#include "my_lib/timer.h"

void show_mpu();
void my_draw();




void MPU9150_setupCompass(){
  i2c_master_write_simple(MPU9150_ADDRESS,MPU9150_USER_CONTROL, 0x00); //Disable Master Aux I2C mode

  i2c_master_write_simple(MPU9150_ADDRESS,MPU9150_INT_PIN_CFG, 0x02); //Enable I2C Aux Bypass mode

  //i2c_master_write_simple = 0x0C;      //change Address to Compass

  i2c_master_write_simple(MPU9150_MAGNO_ADDRESS,MPU9150_MAGNO_CNTRL, 0x01); //Single Read Mode
  delay_ms(10);

 // MPU9150_I2C_ADDRESS = tempAddress; //new version to revert to original address
}




#define FIRST_NAGATIVE_X_NUM 259
#define FIRST_NAGATIVE_Y_NUM 259

#define AA 0x18
#define min_x (-370+FIRST_NAGATIVE_X_NUM)
#define min_y (-384+FIRST_NAGATIVE_Y_NUM)
#define min_z -384
#define max_x 79 //112
#define max_y 52 //96
#define max_z 89 //85

void mpu9150_mag_calibrate()
{
	int mag_x=0;
	int mag_y=0;
	int mag_z=0;
	static int mag_x_max=-5000;
	static mag_y_max=-5000;
	static mag_z_max=-5000;
	static int mag_x_min=5000;
	static mag_y_min=5000;
	static mag_z_min=5000;

	int a=0,b=0;
	int ack;
	ack=i2c_master_write_simple(AA,MPU9150_MAGNO_CNTRL,1);//single read mode

	while((a&1)==0){//wait until stable data receive
		a=i2c_master_read_simple_1Byte(AA,0x02);
	}
	b=i2c_master_read_simple_1Byte(AA,0x09);//if overflow occures
	b=((1<<2)&b)|(b&(1<<3));
	//b=(b&(1<<3));

	if(b==0)
	{

		mag_x=mpu9150_get_mag_x();//single
		mag_y=mpu9150_get_mag_y();//single
		mag_z=mpu9150_get_mag_z();//single
		mag_x_max=(mag_x>mag_x_max&&mag_x<1000&&mag_x>0)?mag_x:mag_x_max;
		mag_y_max=(mag_y>mag_y_max&&mag_y<1000&&mag_y>0)?mag_y:mag_y_max;
		mag_z_max=(mag_z>mag_z_max&&mag_z<1000&&mag_z>0)?mag_z:mag_z_max;
		mag_x_min=(mag_x<mag_x_min&&mag_x>-1000&&mag_x<0)?mag_x:mag_x_min;
		mag_y_min=(mag_y<mag_y_min&&mag_y>-1000&&mag_y<0)?mag_y:mag_y_min;
		mag_z_min=(mag_z<mag_z_min&&mag_z>-1000&&mag_z<0)?mag_z:mag_z_min;

		turn_led(1);
		my_put_int(mag_x_max);//data is ready
		my_putchar('\t');
		my_put_int(mag_y_max );//single
		my_putchar('\t');
		my_put_int(mag_z_max);//single
		my_putchar('\t');
		my_put_int(mag_x_min);//data is ready
		my_putchar('\t');
		my_put_int(mag_y_min );//single
		my_putchar('\t');
		my_put_int(mag_z_min);//single
		my_putchar('\n');


	}

	turn_led(0);


}
//void mpu9150_mag_set_cali()
//{
//	float offset_x = (max_x + min_x) / 2;
//	float offset_y = (max_y + min_y) / 2;
//	float offset_z = (max_z + min_z) / 2;
//
//	float avg_delta_x = (max_x - min_x) / 2;
//	float avg_delta_y = (max_y - min_y) / 2;
//	float avg_delta_z = (max_z - min_z) / 2;
//
//	float avg_delta = (avg_delta_x + avg_delta_y + avg_delta_z) / 3;
//
//	float scale_x = avg_delta / avg_delta_x;
//	float scale_y = avg_delta / avg_delta_y;
//	float scale_z = avg_delta / avg_delta_z;
//
//	float corrected_x = (mag_x - offset_x) * scale_x
//	float corrected_y = (mag_y - offset_y) * scale_y
//	float corrected_z = (mag_z - offset_z) * scale_z
//
//	corrected_x = mag_x - offset_x;
//	corrected_y = mag_y - offset_y;
//	corrected_z = mag_z - offset_z;
//
//}
void mpu9150_degree_mag()
{
	float mag_x=0;
	float mag_y=0;
	float mag_z=0;
	static int angle_x=0;
	static int angle_y=0;
	static int angle_z=0;
	int a=0,b=0;
	int ack;
	ack=i2c_master_write_simple(AA,MPU9150_MAGNO_CNTRL,1);//single read mode


	while((a&1)==0){
		a=i2c_master_read_simple_1Byte(AA,0x02);
	}

	mag_x=mpu9150_get_mag_x();//single
	mag_y=mpu9150_get_mag_y();//single
	mag_z=mpu9150_get_mag_z();//single

	b=i2c_master_read_simple_1Byte(AA,0x09);
	b=((1<<2)&b)|(b&(1<<3));
	if(b==0)
	{

//		my_put_int(mag_x);//single
//		my_putchar('\t');
//
//		my_put_int(mag_y);//single
//		my_putchar('\t');
//		turn_led(0);

		if(mag_y<0)
			mag_y=mag_y+FIRST_NAGATIVE_Y_NUM;//this is the first negative number after zero
		if(mag_x<0)
			mag_x=mag_x+FIRST_NAGATIVE_X_NUM;

//		float offset_x = (max_x + min_x) / 2;
//		float offset_y = (max_y + min_y) / 2;
//		float offset_z = (max_z + min_z) / 2;
//
//		float avg_delta_x = (max_x - min_x) / 2;
//		float avg_delta_y = (max_y - min_y) / 2;
//		//float avg_delta_z = (max_z - min_z) / 2;
//
//		float avg_delta = (avg_delta_x + avg_delta_y) / 2;
//
//		float scale_x = avg_delta / avg_delta_x;
//		float scale_y = avg_delta / avg_delta_y;
//		//float scale_z = avg_delta / avg_delta_z;
//
//		float corrected_x = (mag_x - offset_x) * scale_x;
//		float corrected_y = (mag_y - offset_y) * scale_y;
//		//float corrected_z = (mag_z - offset_z) * scale_z;

		float corrected_x = mag_x /(max_x-min_x);
		float corrected_y = mag_y /(max_y-min_y);
		//corrected_z = mag_z - offset_z;


//		mag_x=corrected_x;
//		mag_y=corrected_y;
//		mag_z=corrected_z;


		if((mag_x==0&&mag_y==0))
			angle_z=0;
		else
			angle_z= (atan2(corrected_y,corrected_x)*180/M_PI); //xy plane

//		if((mag_y==0&&mag_z==0))
//			angle_x=0;
//		else
//			angle_x= (atan2(mag_y,mag_z)*180/M_PI);//yz plane
//
//		if((mag_x==0&&mag_z==0))
//			angle_y=0;
//		else
//			angle_y= (atan2(mag_x,mag_z)*180/M_PI);//zx plane
//		angle_z-=40;
//		angle_x=(angle_x>0)?angle_x:360+angle_x;
//		angle_y=(angle_y>0)?angle_y:360+angle_y;
		angle_z=(angle_z>0)?angle_z:360+angle_z;



		turn_led(1);
		my_put_int(angle_z);//data is ready
//		my_putchar('\t');

//		my_put_int(mag_x);//single
//		my_putchar('\t');

//		my_put_int(mag_y);//single
		my_putchar('\n');
		turn_led(0);
	}

	else
	{
		turn_led(10);
	}


}
int main(void)
{
	my_putstr("\nsalam\n");
	my_put_int(i2c_master_write_simple(MPU9150_ADDRESS,MPU9150_SLEEP_CONFIG,0));
	my_putchar('\n');
	my_put_int(i2c_master_write_simple(MPU9150_ADDRESS,MPU9150_USER_CONTROL,0x00));//disable i2c master
	my_putchar('\n');
	my_put_int(i2c_master_write_simple(MPU9150_ADDRESS,MPU9150_INT_PIN_CFG,0x02));//enable i2c aux
	my_putchar('\n');
	delay_ms(100);
	my_put_int(i2c_master_read_simple_1Byte(AA,0));//single
	my_putchar('\n');
//	my_put_int(i2c_master_write_simple(AA,MPU9150_MAGNO_CNTRL,0x01));//single
	my_putchar('\n');
	delay_ms(10);
	delay_ms(10);
	timer_set_up(5000,LOOP_COUNT);

	IntcLowLevelExample(INTC_BASEADDR);


	delay_ms(10);
	int ack=0;
	while(1){


//		if(i2c_master_write_simple(AA,MPU9150_MAGNO_CNTRL,0x01)==21)
//		{
//			my_putstr("\nOK\t");
//		}
//		else
//		{
//			my_putstr("\nbad\t");
//		}
//		ack=i2c_master_write_simple(AA,MPU9150_MAGNO_CNTRL,0x01);//single read mode
//		my_put_int(i2c_master_read_simple_1Byte(AA,0x00));
//		my_putchar('\n');
		//mpu9150_degree_mag();
		//delay_ms(10);
		//mpu9150_degree_mag();
		//show_mpu();
		//mpu9150_degree_mag();
		show_mpu();
//		mpu9150_mag_calibrate();
	}
	return 0;

}

void show_mpu(){
	static int a=0;
	int OF_X,OF_Y,OF_Z;
	int f_x,f_y,f_z;
	if(a==0){
		mpu9150_init();
		mpu9150_calibrate(&OF_X,&OF_Y,&OF_Z);
		timer_set_up(5000,LOOP_COUNT);

	}
	a=1;
	mpu9150_fuse_data(OF_X,OF_Y,OF_Z,&f_x,&f_y,&f_z);
	my_put_int(mpu9150_make_zero_degree(180,f_x));
	my_putchar('\t');
	my_put_int(mpu9150_make_zero_degree(180,f_y));
	my_putchar('\t');
	my_put_int(mpu9150_make_zero_degree(180,f_z));
	my_putchar('\t');

	my_putchar('\n');

	turn_led(0);

	delay_ms(10);
}
#define PIXEL_SIZE 20
void my_draw(){

	u8 pixel[PIXEL_SIZE][PIXEL_SIZE];
	int i=0,j=0;
	for(;i<PIXEL_SIZE-1;i++){
		for(;j<PIXEL_SIZE-1;j++){
			pixel[i][j]='O';
		}
		j=0;
	}
	i=0,j=0;
	for(;i<PIXEL_SIZE-1;i++){
		for(;j<PIXEL_SIZE-1;j++){
			my_putchar(pixel[i][j]);
			my_putchar(' ');
		}
		my_putchar('\n');
		j=0;
	}


}






