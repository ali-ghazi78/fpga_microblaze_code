################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/i2c/i2c_simple.c \
../src/i2c/i2c_software_master.c \
../src/i2c/i2c_software_master_selftest.c 

OBJS += \
./src/i2c/i2c_simple.o \
./src/i2c/i2c_software_master.o \
./src/i2c/i2c_software_master_selftest.o 

C_DEPS += \
./src/i2c/i2c_simple.d \
./src/i2c/i2c_software_master.d \
./src/i2c/i2c_software_master_selftest.d 


# Each subdirectory must supply rules for building sources it contributes
src/i2c/%.o: ../src/i2c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -IC:/Users/ali/workspace_fpga_sdk/the_one_worked_4_bsp/microblaze_0/include -c -fmessage-length=0 -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


