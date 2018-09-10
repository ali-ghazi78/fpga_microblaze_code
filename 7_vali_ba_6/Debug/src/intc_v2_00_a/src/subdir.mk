################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/intc_v2_00_a/src/xintc.c \
../src/intc_v2_00_a/src/xintc_g.c \
../src/intc_v2_00_a/src/xintc_intr.c \
../src/intc_v2_00_a/src/xintc_l.c \
../src/intc_v2_00_a/src/xintc_options.c \
../src/intc_v2_00_a/src/xintc_selftest.c 

OBJS += \
./src/intc_v2_00_a/src/xintc.o \
./src/intc_v2_00_a/src/xintc_g.o \
./src/intc_v2_00_a/src/xintc_intr.o \
./src/intc_v2_00_a/src/xintc_l.o \
./src/intc_v2_00_a/src/xintc_options.o \
./src/intc_v2_00_a/src/xintc_selftest.o 

C_DEPS += \
./src/intc_v2_00_a/src/xintc.d \
./src/intc_v2_00_a/src/xintc_g.d \
./src/intc_v2_00_a/src/xintc_intr.d \
./src/intc_v2_00_a/src/xintc_l.d \
./src/intc_v2_00_a/src/xintc_options.d \
./src/intc_v2_00_a/src/xintc_selftest.d 


# Each subdirectory must supply rules for building sources it contributes
src/intc_v2_00_a/src/%.o: ../src/intc_v2_00_a/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../7_vali_ba_6_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


