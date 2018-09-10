/*****************************************************************************
* Filename:          D:\fpga_project\cpu\24_axi/drivers/led_v1_00_a/src/led.c
* Version:           1.00.a
* Description:       led Driver Source File
* Date:              Tue Aug 21 16:38:36 2018 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "led.h"

/************************** Function Definitions ***************************/

#define LED_K_BASE_AD 0x7b400000

void turn_led(u8 data)
{
	LED_mWriteReg(LED_K_BASE_AD,LED_SLV_REG0_OFFSET,data<<24);
}
