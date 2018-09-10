/*****************************************************************************
* Filename:          F:\xilinx\embeded_development_kit\14.7\ISE_DS\edk_user_repository\MyProcessorIPLib/drivers/timer_v1_00_a/src/timer.c
* Version:           1.00.a
* Description:       timer Driver Source File
* Date:              Wed Aug 22 03:38:23 2018 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "timer.h"
#include "xil_types.h"
#define BASSE_ADD_TIMER 0x72400000
/************************** Function Definitions ***************************/

//timer t1(
//.turn_on(slv_reg1[0]),
//.prescaler(slv_reg0[15:0]),
//.clock(clock),
//.reset(reset),
//.top(slv_reg0[31:16]),
//.interupt(interupt)
//    );

void timer_on(){
	TIMER_mWriteSlaveReg1(BASSE_ADD_TIMER,TIMER_SLV_REG1_OFFSET,1);
}
void timer_off(){
	TIMER_mWriteSlaveReg1(BASSE_ADD_TIMER,TIMER_SLV_REG1_OFFSET,0);
}
void timer_set_up(u16 prescaler,u16 top){
	u32 package=prescaler|(top<<16);
	TIMER_mWriteSlaveReg0(BASSE_ADD_TIMER,TIMER_SLV_REG0_OFFSET,package);
}
