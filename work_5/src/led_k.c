/*****************************************************************************
* Filename:          D:\fpga_project\cpu\23/drivers/led_k_v2_00_a/src/led_k.c
* Version:           2.00.a
* Description:       led_k Driver Source File
* Date:              Fri Aug 03 21:42:17 2018 (by Create and Import Peripheral Wizard)
*****************************************************************************/

/***************************** Include Files *******************************/

#include "led_k.h"
/************************** Function Definitions ***************************/
#define LED_K_BASE_AD 0xc3400000

void turn_led(u8 data)
{
	LED_K_mWriteSlaveReg0(LED_K_BASE_AD,LED_K_SLV_REG0_OFFSET,data);
}
