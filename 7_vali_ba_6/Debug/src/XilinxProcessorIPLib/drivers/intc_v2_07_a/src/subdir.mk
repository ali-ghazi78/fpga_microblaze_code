################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc.c \
../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_g.c \
../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_intr.c \
../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_l.c \
../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_options.c \
../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_selftest.c 

OBJS += \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc.o \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_g.o \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_intr.o \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_l.o \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_options.o \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_selftest.o 

C_DEPS += \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc.d \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_g.d \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_intr.d \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_l.d \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_options.d \
./src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/xintc_selftest.d 


# Each subdirectory must supply rules for building sources it contributes
src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/%.o: ../src/XilinxProcessorIPLib/drivers/intc_v2_07_a/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../7_vali_ba_6_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


