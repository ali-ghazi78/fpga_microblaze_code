################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/helloworld.c \
../src/platform.c \
../src/usart.c \
../src/usart_selftest.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/helloworld.o \
./src/platform.o \
./src/usart.o \
./src/usart_selftest.o 

C_DEPS += \
./src/helloworld.d \
./src/platform.d \
./src/usart.d \
./src/usart_selftest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../the_one_that_sh_work_2_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


