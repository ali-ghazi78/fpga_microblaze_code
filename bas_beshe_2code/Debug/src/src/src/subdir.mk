################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/src/src/delay.c \
../src/src/src/i2c.c \
../src/src/src/led.c \
../src/src/src/mpu6050.c \
../src/src/src/timer.c \
../src/src/src/usart.c 

OBJS += \
./src/src/src/delay.o \
./src/src/src/i2c.o \
./src/src/src/led.o \
./src/src/src/mpu6050.o \
./src/src/src/timer.o \
./src/src/src/usart.o 

C_DEPS += \
./src/src/src/delay.d \
./src/src/src/i2c.d \
./src/src/src/led.d \
./src/src/src/mpu6050.d \
./src/src/src/timer.d \
./src/src/src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/src/src/%.o: ../src/src/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../bas_beshe_2code_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


