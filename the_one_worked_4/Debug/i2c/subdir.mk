################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../i2c/i2c_simple.c \
../i2c/i2c_software_master.c \
../i2c/i2c_software_master_selftest.c 

OBJS += \
./i2c/i2c_simple.o \
./i2c/i2c_software_master.o \
./i2c/i2c_software_master_selftest.o 

C_DEPS += \
./i2c/i2c_simple.d \
./i2c/i2c_software_master.d \
./i2c/i2c_software_master_selftest.d 


# Each subdirectory must supply rules for building sources it contributes
i2c/%.o: ../i2c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../the_one_worked_4_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


