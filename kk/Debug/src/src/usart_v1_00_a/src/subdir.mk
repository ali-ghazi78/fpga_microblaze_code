################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/src/usart_v1_00_a/src/usart.o 

C_SRCS += \
../src/src/usart_v1_00_a/src/usart.c 

OBJS += \
./src/src/usart_v1_00_a/src/usart.o 

C_DEPS += \
./src/src/usart_v1_00_a/src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/src/usart_v1_00_a/src/%.o: ../src/src/usart_v1_00_a/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../kk_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


