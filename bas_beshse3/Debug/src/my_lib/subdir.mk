################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/my_lib/delay.c \
../src/my_lib/i2c.c \
../src/my_lib/led.c \
../src/my_lib/mpu6050.c \
../src/my_lib/timer.c \
../src/my_lib/usart.c 

OBJS += \
./src/my_lib/delay.o \
./src/my_lib/i2c.o \
./src/my_lib/led.o \
./src/my_lib/mpu6050.o \
./src/my_lib/timer.o \
./src/my_lib/usart.o 

C_DEPS += \
./src/my_lib/delay.d \
./src/my_lib/i2c.d \
./src/my_lib/led.d \
./src/my_lib/mpu6050.d \
./src/my_lib/timer.d \
./src/my_lib/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/my_lib/%.o: ../src/my_lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../bas_beshse3_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


