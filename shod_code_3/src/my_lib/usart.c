/*****************************************************************************
* Filename:          D:\fpga_project\cpu\23/drivers/usart_v4_00_a/src/usart.c
* Version:           4.00.a
* Description:       usart Driver Source File
* Date:              Sat Aug 04 04:38:19 2018 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "usart.h"
#include "led.h"

/************************** Function Definitions ***************************/
const u16 PRESCALER=1250;//12mhz / 9600 =1250

void my_put_int( int number)
{

	 int counter=0;
	 if(number<0)
	 {
		 usart_putchar('-',PRESCALER);
		number*=-1;
	 }
	 int temp=number;
	 while (temp)
	 {
		 counter++;
		 temp/=10;
	 }
	 temp=number;
	 while(counter&&counter!=1)
	 {
		 usart_putchar(number/my_pow(10,counter-1)+'0',PRESCALER);
		if(counter>2)
			number%=(int)my_pow(10,counter-1);
		else
			break;
		counter--;
	 }
	 usart_putchar(temp%10+'0',PRESCALER);

}
unsigned int  my_pow(int base ,int pow)
{
	unsigned int  data=1;
	for(;pow;pow--)
	{
		data*=base;
	}
	return data;
}
void my_putstr(char  p[])
{
	int i=0;
	for(;p[i]!='\0';i++)
	{
		usart_putchar(p[i],PRESCALER);
	}
}


void usart_putchar(u8 data,u16 prescaler)
{
	u32 packet=0;
	//int i=0,status;
	packet=(1<<24);
	USART_TX1_mWriteSlaveReg0(USART_BASE_AD,0,packet);
	packet|=prescaler;
	packet|=data<<16;
	USART_TX1_mWriteSlaveReg0(USART_BASE_AD,0,packet);//loading data

	packet&=~(1<<24);
	USART_TX1_mWriteSlaveReg0(USART_BASE_AD,0,packet);//transmit data
	while((usart_get_status()&1)&&1);//this is too dangerous . we are waiting for axi delay to send data
	while(!((usart_get_status()&(1<<0))&&1));
	packet=(1<<24);
	USART_TX1_mWriteSlaveReg0(USART_BASE_AD,0,packet);//loading data
}
void my_putchar(u8 data){
	usart_putchar(data,PRESCALER);
}

u32 usart_get_status()
{
	return USART_TX1_mReadSlaveReg1(USART_BASE_AD,0);
}
void exception(char *string,float number,int div)
{
		my_putstr("\n");
        my_putstr(string);
        my_putstr("{");
        my_put_int(number);
        my_putstr("}\n");
}

