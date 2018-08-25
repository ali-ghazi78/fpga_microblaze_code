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
#include "my_lib/mpu6050.h"
#include "my_lib/usart.h"
#include "my_lib/timer.h"

int main(void)
{

	int OF_X,OF_Y,OF_Z;
	mpu6050_init();
	mpu_calibrate(&OF_X,&OF_Y,&OF_Z);

	my_putstr("salam\n");
	turn_led(1);
	delay_ms(LOOP_COUNT);
	IntcLowLevelExample(INTC_BASEADDR);

	timer_set_up(5000,LOOP_COUNT);
	while(1){

		mpu_fuse_data(OF_X,OF_Y,OF_Z);
		my_put_int(make_zero_degree(180,fused_x));
		my_putchar('\t');
		my_put_int(make_zero_degree(180,fused_y));
		my_putchar('\t');
		my_put_int(make_zero_degree(180,fused_z));
		my_putchar('\n');
		turn_led(0);

		delay_ms(10);
	}
	return 0;

}









