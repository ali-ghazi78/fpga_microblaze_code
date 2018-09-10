##############################################################################
## Filename:          F:\xilinx\embeded_development_kit\14.7\ISE_DS\edk_user_repository\MyProcessorIPLib/drivers/led_v1_00_a/data/led_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Tue Aug 21 22:14:24 2018 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "led" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
