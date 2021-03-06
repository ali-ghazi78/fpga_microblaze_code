/*****************************************************************************
* Filename:          F:\xilinx\embeded_development_kit\14.7\ISE_DS\edk_user_repository\MyProcessorIPLib/drivers/usart_tx1_v1_00_a/src/usart_tx1.h
* Version:           1.00.a
* Description:       usart_tx1 Driver Header File
* Date:              Wed Aug 22 00:11:04 2018 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef USART_TX1_H
#define USART_TX1_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"
#include "xil_types.h"
#include "my_param.h"


/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 * -- SLV_REG0 : user logic slave module register 0
 * -- SLV_REG1 : user logic slave module register 1
 */
#define USART_TX1_USER_SLV_SPACE_OFFSET (0x00000000)
#define USART_TX1_SLV_REG0_OFFSET (USART_TX1_USER_SLV_SPACE_OFFSET + 0x00000000)
#define USART_TX1_SLV_REG1_OFFSET (USART_TX1_USER_SLV_SPACE_OFFSET + 0x00000004)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a USART_TX1 register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the USART_TX1 device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void USART_TX1_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define USART_TX1_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a USART_TX1 register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the USART_TX1 device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 USART_TX1_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define USART_TX1_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from USART_TX1 user logic slave registers.
 *
 * @param   BaseAddress is the base address of the USART_TX1 device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void USART_TX1_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 USART_TX1_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define USART_TX1_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (USART_TX1_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define USART_TX1_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (USART_TX1_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))

#define USART_TX1_mReadSlaveReg0(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (USART_TX1_SLV_REG0_OFFSET) + (RegOffset))
#define USART_TX1_mReadSlaveReg1(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (USART_TX1_SLV_REG1_OFFSET) + (RegOffset))

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the USART_TX1 instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus USART_TX1_SelfTest(void * baseaddr_p);


void my_put_int( int number);
unsigned int  my_pow(int base ,int pow);
void my_putstr(u8 *p);
void usart_putchar(u8 data,u16 prescaler);
void my_putchar(u8 data);
u32 usart_get_status();




/**
*  Defines the number of registers available for read and write*/
#define TEST_AXI_LITE_USER_NUM_REG_USART 2


#endif /** USART_TX1_H */
