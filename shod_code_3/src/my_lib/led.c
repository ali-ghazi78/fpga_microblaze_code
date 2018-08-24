/*****************************************************************************
* Filename:          F:\xilinx\embeded_development_kit\14.7\ISE_DS\edk_user_repository\MyProcessorIPLib/drivers/led_v1_00_a/src/led.c
* Version:           1.00.a
* Description:       led Driver Source File
* Date:              Tue Aug 21 22:14:24 2018 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "led.h"
/************************** Function Definitions ***************************/
void turn_led (unsigned char data)
{
    LED_mWriteSlaveReg0(BASE_ADD_LED,0,data);
}
