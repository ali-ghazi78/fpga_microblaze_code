################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/build/vxworks5_4/xtag_csp_intc_v1_10_c.c 

OBJS += \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/build/vxworks5_4/xtag_csp_intc_v1_10_c.o 

C_DEPS += \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/build/vxworks5_4/xtag_csp_intc_v1_10_c.d 


# Each subdirectory must supply rules for building sources it contributes
src/XilinxProcessorIPLib/drivers/intc_v2_07_a/build/vxworks5_4/%.o: ../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/build/vxworks5_4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../7_vali_ba_6_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


