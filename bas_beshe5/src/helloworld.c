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

//#include <stdio.h>
//#include "my_lib/led.h"
//#include "my_lib/delay.h"
//int main()
//{
//	while(1){
//		turn_led(5);
//		delay_ms(50);
//		turn_led(0);
//		delay_ms(50);
//	}
//    return 0;
//}
/******************************************************************************
*
* (c) Copyright 2002-2013 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/
/******************************************************************************/
/**
*
* @file xintc_example.c
*
* This file contains a design example using the Interrupt Controller driver
* (XIntc) and hardware device. Please reference other device driver examples to
* see more examples of how the intc and interrupts can be used by a software
* application.
*
* This example shows the use of the Interrupt Controller both with a PowerPC
* and MicroBlaze processor.
*
* @note
*		This example can also be used for Cascade mode interrupt
*		controllers by using the interrupt IDs generated in
*		xparameters.h. For Cascade mode, Interrupt IDs are generated
*		in xparameters.h as shown below:
*
*	    Master/Primary INTC
*		 ______
*		|      |-0      Secondary INTC
*		|      |-.         ______
*		|      |-.        |      |-32        Last INTC
*		|      |-.        |      |-.          ______
*		|______|<--31-----|      |-.         |      |-64
*			          |      |-.         |      |-.
*			          |______|<--63------|      |-.
*                                                    |      |-.
*                                                    |______|-95
*
*		All driver functions has to be called using
*		DeviceId/InstancePtr of Primary/Master Controller only. Driver
*		functions takes care of Slave Controllers based on Interrupt
*		ID passed. User must not use Interrupt source/ID  31 of Primary
*		and Secondary controllers to call driver functions.
*
* <pre>
*
* MODIFICATION HISTORY:
* Ver   Who  Date	 Changes
* ----- ---- -------- ----------------------------------------------------
* 1.00b jhl  02/13/02 First release
* 1.00c rpm  11/13/03 Updated to show microblaze and PPC interrupt use and
*		      to use the common L0/L1 interrupt handler with device ID.
* 1.00c sv   06/29/05 Minor changes to comply to Doxygen and coding guidelines
* 2.00a ktn  10/20/09 Updated to use HAL Processor APIs amd minor modifications
*		      as per coding guidelines.
* </pre>
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xstatus.h"
#include "xintc.h"
#include "xil_exception.h"

/************************** Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define INTC_DEVICE_ID		  XPAR_INTC_0_DEVICE_ID

/*
 *  This is the Interrupt Number of the Device whose Interrupt Output is
 *  connected to the Input of the Interrupt Controller
 */
#define INTC_DEVICE_INT_ID	  0


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

int IntcExample(u16 DeviceId);

int SetUpInterruptSystem(XIntc *XIntcInstancePtr);

void DeviceDriverHandler(void *CallbackRef);


/************************** Variable Definitions *****************************/

static XIntc InterruptController; /* Instance of the Interrupt Controller */

/*
 * Create a shared variable to be used by the main thread of processing and
 * the interrupt processing
 */
volatile static int InterruptProcessed = FALSE;

/*****************************************************************************/
/**
*
* This is the main function for the Interrupt Controller example.
*
* @param	None.
*
* @return	XST_SUCCESS to indicate success, otherwise XST_FAILURE.
*
* @note		None.
*
****************************************************************************/
#include "my_lib/led.h"
#include "my_lib/delay.h"
int main(void)
{
	int Status;

	/*
	 * Run the Intc example , specify the Device ID generated in
	 * xparameters.h
	 */
	Status = IntcExample(INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		turn_led(255);
	}

	while(1){
		turn_led(255);
	}


	return XST_SUCCESS;
}


/*****************************************************************************/
/**
*
* This function is an example of how to use the interrupt controller driver
* component (XIntc) and the hardware device.  This function is designed to
* work without any hardware devices to cause interrupts.  It may not return
* if the interrupt controller is not properly connected to the processor in
* either software or hardware.
*
* This function relies on the fact that the interrupt controller hardware
* has come out of the reset state such that it will allow interrupts to be
* simulated by the software.
*
* @param	DeviceId is Device ID of the Interrupt Controller Device,
*		typically XPAR_<INTC_instance>_DEVICE_ID value from
*		xparameters.h.
*
* @return	XST_SUCCESS to indicate success, otherwise XST_FAILURE.
*
* @note		None.
*
******************************************************************************/
int IntcExample(u16 DeviceId)
{
	int Status;

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	Status = XIntc_Initialize(&InterruptController, DeviceId);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Perform a self-test to ensure that the hardware was built
	 * correctly.
	 */
//	Status = XIntc_SelfTest(&InterruptController);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}


	/*
	 * Setup the Interrupt System.
	 */
	Status = SetUpInterruptSystem(&InterruptController);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 *  Simulate the Interrupt.
	 */
//	Status = XIntc_SimulateIntr(&InterruptController, INTC_DEVICE_INT_ID);
//	if (Status != XST_SUCCESS) {
//		return XST_FAILURE;
//	}


	/*
	 * Wait for the interrupt to be processed, if the interrupt does not
	 * occur this loop will wait forever.
	 */
	while (1)
	{
		/*
		 * If the interrupt occurred which is indicated by the global
		 * variable which is set in the device driver handler, then
		 * stop waiting.
		 */
		if (InterruptProcessed) {
			turn_led(2);
			break;
		}
		turn_led(5);
		delay_ms(1000);
		turn_led(0);
		delay_ms(1000);

	}

	return XST_SUCCESS;

}

/******************************************************************************/
/**
*
* This function connects the interrupt handler of the interrupt controller to
* the processor.  This function is seperate to allow it to be customized for
* each application.  Each processor or RTOS may require unique processing to
* connect the interrupt handler.
*
* @param	None.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
int SetUpInterruptSystem(XIntc *XIntcInstancePtr)
{
	int Status;


	/*
	 * Connect a device driver handler that will be called when an interrupt
	 * for the device occurs, the device driver handler performs the
	 * specific interrupt processing for the device.
	 */
	Status = XIntc_Connect(XIntcInstancePtr, INTC_DEVICE_INT_ID,
				   (XInterruptHandler)DeviceDriverHandler,
				   (void *)0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts, specify simulation mode so that
	 * an interrupt can be caused by software rather than a real hardware
	 * interrupt.
	 */
	Status = XIntc_Start(XIntcInstancePtr, XIN_SIMULATION_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Enable the interrupt for the device and then cause (simulate) an
	 * interrupt so the handlers will be called.
	 */
	XIntc_Enable(XIntcInstancePtr, INTC_DEVICE_INT_ID);

	/*
	 * Initialize the exception table.
	 */
	Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler)XIntc_InterruptHandler,
				XIntcInstancePtr);

	/*
	 * Enable exceptions.
	 */
	Xil_ExceptionEnable();

	return XST_SUCCESS;

}

/******************************************************************************/
/**
*
* This function is designed to look like an interrupt handler in a device
* driver. This is typically a 2nd level handler that is called from the
* interrupt controller interrupt handler.  This handler would typically
* perform device specific processing such as reading and writing the registers
* of the device to clear the interrupt condition and pass any data to an
* application using the device driver.  Many drivers already provide this
* handler and the user is not required to create it.
*
* @param	CallbackRef is passed back to the device driver's interrupt
*		handler by the XIntc driver.  It was given to the XIntc driver
*		in the XIntc_Connect() function call.  It is typically a pointer
*		to the device driver instance variable if using the Xilinx
*		Level 1 device drivers.  In this example, we do not care about
*		the callback reference, so we passed it a 0 when connecting the
*		handler to the XIntc driver and we make no use of it here.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void DeviceDriverHandler(void *CallbackRef)
{
	/*
	 * Indicate the interrupt has been processed using a shared variable.
	 */
	InterruptProcessed = TRUE;
	turn_led(255);
	delay_ms(1000);

}
