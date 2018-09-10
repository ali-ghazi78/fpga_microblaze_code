################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cpu/21/drivers/usart_v1_00_a/src/usart.c \
../src/cpu/21/drivers/usart_v1_00_a/src/usart_selftest.c 

OBJS += \
./src/cpu/21/drivers/usart_v1_00_a/src/usart.o \
./src/cpu/21/drivers/usart_v1_00_a/src/usart_selftest.o 

C_DEPS += \
./src/cpu/21/drivers/usart_v1_00_a/src/usart.d \
./src/cpu/21/drivers/usart_v1_00_a/src/usart_selftest.d 


# Each subdirectory must supply rules for building sources it contributes
src/cpu/21/drivers/usart_v1_00_a/src/%.o: ../src/cpu/21/drivers/usart_v1_00_a/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../ff_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


