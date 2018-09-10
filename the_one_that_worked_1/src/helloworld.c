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

#include <stdio.h>
#include "platform.h"
#include "led_k.h"
#include "mblaze_nt_types.h"
#include "usart.h"

#define LED_K_BASE_AD 0xc3400000
#define USART_BASE_AD 0xce200000

void turn_led(u8 data);
u32 usart_get_status();
void delay(uint32_t delay_ms);
void usart_putchar(u16 prescaler,u8 data);

int main()
{
	uint32_t status;
	int i=0;
	while(1)
		usart_putchar(1250,'a');

	return 0;
}
void usart_putchar(u16 prescaler,u8 data)
{
	u32 packet=0;
	int i=0;
	/*
	  my_usart mm(
	  .clock(clock),
	  .reset(Bus2IP_Reset),
	  .led(led),
	  .prescaler(slv_reg0[16:31]),
	  .data(slv_reg0[8:15]),
	  .tx_pin(tx_pin),
	  .transmit(slv_reg0[7]),
	  .uart_busy(slv_output_temp_signal[31])
	  );
    */

	packet=1<<24;
	USART_mWriteSlaveReg0(USART_BASE_AD,USART_SLV_REG0_OFFSET,packet);	//clearing transmit
	delay(1000);
	turn_led(1);
	packet|=prescaler;
	packet|=data<<16;
	USART_mWriteSlaveReg0(USART_BASE_AD,USART_SLV_REG0_OFFSET,packet);	//loading data
	delay(100);
	turn_led(3);
	packet&=~(1<<24);
	delay(100);
	turn_led(7);
	packet=(1<<24);
	USART_mWriteSlaveReg0(USART_BASE_AD,USART_SLV_REG0_OFFSET,packet);	//clearing transmit
	delay(1000);
	turn_led(0);
}
u32 usart_get_status()
{
	return USART_mReadSlaveReg1(USART_BASE_AD,USART_SLV_REG1_OFFSET);
}
void turn_led(u8 data)
{
	LED_K_mWriteSlaveReg0(LED_K_BASE_AD,LED_K_SLV_REG0_OFFSET,data);
}
void delay(uint32_t delay_ms)
{
	int i=0,k=0,j=0;
	for( ;i<10000;i++)
		for( ;k<10000;k++)
			for(;j<2500*delay_ms;j++);
}
