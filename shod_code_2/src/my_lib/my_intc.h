/***************************** Include Files *********************************/

#include "xparameters.h"
#include "xstatus.h"
#include "xintc_l.h"
#include "xil_exception.h"
#include "delay.h"
#include "led.h"


int counter_mpu;

/************************ Constant Definitions *****************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define INTC_BASEADDR		XPAR_INTC_0_BASEADDR
#define INTC_DEVICE_ID		XPAR_INTC_0_DEVICE_ID
#define INTC_DEVICE_INTR_ID	0
#define INTC_DEVICE_INT_MASK	1


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

int IntcLowLevelExample(u32 IntcBaseAddress);

void SetupInterruptSystem();

void DeviceDriverHandler(void *CallbackRef);
void timer_call_back();


/************************** Variable Definitions *****************************/

/*
 * Create a shared variable to be used by the main thread of processing and
 * the interrupt processing
 */
volatile static int InterruptProcessed = FALSE;

