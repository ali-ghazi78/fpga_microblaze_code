#include "mpu9150.h"

extern int counter_mpu9150;

void mpu9150_init(){
	i2c_master_write_simple(MPU9150_ADDRESS,MPU9150_SLEEP_CONFIG,0);
	i2c_master_write_simple(MPU9150_ADDRESS,MPU9150_GYRO_CONFIG,0);
	i2c_master_write_simple(MPU9150_ADDRESS,MPU9150_SAMPLE_RATE,0);

}
char mpu9150_get_name(){
	return i2c_master_read_simple_1Byte(MPU9150_ADDRESS,MPU9150_WHO_AM);
}
int mpu9150_get_gyro_x(){
	return i2c_master_read_simple_2Byte(MPU9150_ADDRESS,G_X_H);
}
int mpu9150_get_gyro_y(){
	return i2c_master_read_simple_2Byte(MPU9150_ADDRESS,G_Y_H);
}
int mpu9150_get_gyro_z(){
	return i2c_master_read_simple_2Byte(MPU9150_ADDRESS,G_Z_H);
}
signed int  mpu9150_get_accel_x(){
	return i2c_master_read_simple_2Byte(MPU9150_ADDRESS,A_X_H);
}
int mpu9150_get_accel_y(){
	return i2c_master_read_simple_2Byte(MPU9150_ADDRESS,A_Y_H);
}
int mpu9150_get_accel_z(){
	return i2c_master_read_simple_2Byte(MPU9150_ADDRESS,A_Z_H);
}
//---------------magnometer------------------
int mpu9150_get_mag_x(){
	int data1=i2c_master_read_simple_1Byte(MPU9150_MAGNO_ADDRESS,M_X_L);
	int data2=i2c_master_read_simple_1Byte(MPU9150_MAGNO_ADDRESS,M_X_H);
	data2*=256;
	data2+=data1;
	return data2;
}
int mpu9150_get_mag_y(){
	int data=i2c_master_read_simple_1Byte(MPU9150_MAGNO_ADDRESS,M_Y_H);
	data*=256;
	data+=i2c_master_read_simple_1Byte(MPU9150_MAGNO_ADDRESS,M_Y_L);
	return data;
}
int mpu9150_get_mag_z(){
	int data=i2c_master_read_simple_1Byte(MPU9150_MAGNO_ADDRESS,M_Z_H);
	data*=256;
	data+=i2c_master_read_simple_1Byte(MPU9150_MAGNO_ADDRESS,M_Z_L);
	return data;
}

//-------------------------------------------------

float mpu9150_make_zero_degree(int zero,int degree)
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
void mpu9150_fuse_data(int OFF_X,int OFF_Y,int OFF_Z,int *f_x,int *f_y,int *f_z)
{

	int t_x,t_y,t_z;
	float CO_A=.98;
	float CO_B=.02;
	int p_x,p_y,p_z;

	static float deg_accel_z_2,deg_accel_x_2,deg_accel_y_2;
	static float g_x,g_y,g_z;
	static float a_x,a_y,a_z;
	static float degree_x,degree_y,degree_z;
	static float fused_x,fused_y,fused_z;
	int T1,T2;

	t_x=g_x;
	t_y=g_y;
	t_z=g_z;

	p_x=a_x;
	p_y=a_y;
	p_z=a_z;

	mpu9150_degree_mag(&T1,&T2);
	int angle_mag_x=T1;
	int angle_mag_y=T2;

	g_x=(float)mpu9150_get_gyro_x()-OFF_X;
	g_y=(float)mpu9150_get_gyro_y()-OFF_Y;
	g_z=(float)mpu9150_get_gyro_z()-OFF_Z;

	a_x=mpu9150_get_accel_x();
	a_y=mpu9150_get_accel_y();
	a_z=mpu9150_get_accel_z();

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
			fused_x=(((float)g_x*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME)+fused_x)*CO_A+deg_accel_x_2*CO_B;
	}
	else if(fused_x<deg_accel_x_2)
	{
		if((deg_accel_x_2-fused_x)>180)
			fused_x=deg_accel_x_2;
		else
			fused_x=(((float)g_x*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME)+fused_x)*CO_A+deg_accel_x_2*CO_B;

	}
	//////////y

	if(fused_y>deg_accel_y_2)
	{
		if((fused_y-deg_accel_y_2)>180)
			fused_y=deg_accel_y_2;
		else
			fused_y=(((float)g_y*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME)+fused_y)*CO_A+deg_accel_y_2*CO_B;
	}
	else if(fused_y<deg_accel_y_2)
	{
		if((deg_accel_y_2-fused_y)>180)
			fused_y=deg_accel_y_2;
		else
			fused_y=(((float)g_y*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME)+fused_y)*CO_A+deg_accel_y_2*CO_B;
	}
	//////////z

	if(fused_z>deg_accel_z_2)
	{
		if((fused_z-deg_accel_z_2)>180)
			fused_z=deg_accel_z_2;
		else
			fused_z=(((float)g_z*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME)+fused_z)*CO_A+deg_accel_z_2*CO_B;
	}
	else if(fused_z<deg_accel_z_2)
	{
		if((deg_accel_z_2-fused_z)>180)
			fused_z=deg_accel_z_2;
		else
			fused_z=(((float)g_z*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME)+fused_z)*CO_A+deg_accel_z_2*CO_B;
	}

	//
	//    fused_y=(((float)g_y*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME)+fused_y)*.98+deg_accel_y_2*.02;
	//    fused_z=(((float)g_z*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME)+fused_z)*.98+deg_accel_z_2*.02;


	degree_x+=((float)g_x*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME);
	degree_y+=((float)g_y*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME);
	degree_z+=((float)g_z*(float)((long)counter_mpu9150*LOOP_COUNT+(timer_currenct_counter()))*(float)TIME);

	counter_mpu9150=0;
	timer_set_up(5000,LOOP_COUNT);
	timer_on();
	while((fused_x>360)||(fused_y>360)||(fused_z>360))
	{
		if(fused_x>360){
			//exception("fused_x",fused_x,0);
			//my_putchar('c');
			fused_x=fused_x-360;
		}
		if(fused_y>360){
			//my_putchar('d');
			fused_y=fused_y-360;
		}
		if(fused_z>360){
			//my_putchar('d');
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
	*f_x=fused_x;
	*f_y=fused_y;
	*f_z=fused_z;
}

void mpu9150_calibrate(int *OFFSET_X,int *OFFSET_Y,int *OFFSET_Z)
{
	int i=0;

    my_putstr("\n----------start_calibratin-------\n");

    for(;i<500;i++)
    {
           *OFFSET_X=(float)mpu9150_get_gyro_x();
           *OFFSET_Y=(float)mpu9150_get_gyro_y();
           *OFFSET_Z=(float)mpu9150_get_gyro_z();
    }
    i=0;
    for(;i<50;i++)
    {
           *OFFSET_X+=mpu9150_get_gyro_x();
           *OFFSET_Y+=mpu9150_get_gyro_y();
           *OFFSET_Z+=mpu9150_get_gyro_z();
    }
    *OFFSET_X/=50;
    *OFFSET_Y/=50;
    *OFFSET_Z/=50;

    exception("G_x_OFFSET",*OFFSET_X,0);
    exception("G_y_OFFSET",*OFFSET_Y,0);
    exception("G_z_OFFSET",*OFFSET_Z,0);

    delay_ms(500);
    my_putstr("\n----------finish_calibratin-------\n");
}
//---------------magnetometer -------
void mpu9150_degree_mag(int *_angle_x,int *_angle_y)
{
	float mag_x=0;
	float mag_y=0;
	float mag_z=0;
	static int angle_x=0;
	static int angle_y=0;
	static int angle_z=0;
	int a=0,b=0;
	int ack;
	ack=i2c_master_write_simple(MPU9150_MAGNO_ADDRESS,MPU9150_MAGNO_CNTRL,1);//single read mode


	while((a&1)==0){
		a=i2c_master_read_simple_1Byte(MPU9150_MAGNO_ADDRESS,0x02);
	}

	mag_x=mpu9150_get_mag_x();//single
	mag_y=mpu9150_get_mag_y();//single
	mag_z=mpu9150_get_mag_z();//single

	b=i2c_master_read_simple_1Byte(MPU9150_MAGNO_ADDRESS,0x09);
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
//---------show mpu---

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



