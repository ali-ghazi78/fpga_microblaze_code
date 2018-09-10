################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/my_libs/delay.c \
../src/my_libs/i2c_simple.c \
../src/my_libs/led_k.c \
../src/my_libs/main.c \
../src/my_libs/mpu6050.c \
../src/my_libs/platform.c \
../src/my_libs/usart.c 

LD_SRCS += \
../src/my_libs/lscript.ld 

OBJS += \
./src/my_libs/delay.o \
./src/my_libs/i2c_simple.o \
./src/my_libs/led_k.o \
./src/my_libs/main.o \
./src/my_libs/mpu6050.o \
./src/my_libs/platform.o \
./src/my_libs/usart.o 

C_DEPS += \
./src/my_libs/delay.d \
./src/my_libs/i2c_simple.d \
./src/my_libs/led_k.d \
./src/my_libs/main.d \
./src/my_libs/mpu6050.d \
./src/my_libs/platform.d \
./src/my_libs/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/my_libs/%.o: ../src/my_libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../axi_prj_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


