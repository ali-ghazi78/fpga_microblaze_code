/*****************************************************************************
* Filename:          F:\xilinx\embeded_development_kit\14.7\ISE_DS\edk_user_repository\MyProcessorIPLib/drivers/timer_v1_00_a/src/timer.c
* Version:           1.00.a
* Description:       timer Driver Source File
* Date:              Wed Aug 22 03:38:23 2018 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "timer.h"

/************************** Function Definitions ***************************/


//  	timer myT(
//	.prescaler(slv_reg0[15:0]),
//	.top(slv_reg0[31:16]),
//	.counter_now(slv_reg1[15:0]),
//	.turn_on(slv_reg2[0]),
//	.clock(clock),
//	.reset(reset),
//	.interupt(interrupt)
//	);
//

void timer_on(){
	TIMER_mWriteSlaveReg2(BASSE_ADD_TIMER,0,1);

}
void timer_off(){
	TIMER_mWriteSlaveReg2(BASSE_ADD_TIMER,0,0);
}
void timer_set_up(u16 prescaler,u16 top){
	u32 package=prescaler|(top<<16);
	TIMER_mWriteSlaveReg0(BASSE_ADD_TIMER,0,package);
}
u16 timer_currenct_counter(){
	return TIMER_mReadSlaveReg1(BASSE_ADD_TIMER,0);

}
