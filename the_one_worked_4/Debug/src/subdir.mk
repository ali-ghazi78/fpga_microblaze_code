################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/delay.c \
../src/i2c_simple.c \
../src/led_k.c \
../src/main.c \
../src/platform.c \
../src/usart.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/delay.o \
./src/i2c_simple.o \
./src/led_k.o \
./src/main.o \
./src/platform.o \
./src/usart.o 

C_DEPS += \
./src/delay.d \
./src/i2c_simple.d \
./src/led_k.d \
./src/main.d \
./src/platform.d \
./src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -IC:/Users/ali/workspace_fpga_sdk/the_one_worked_4_bsp/microblaze_0/include -c -fmessage-length=0 -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


