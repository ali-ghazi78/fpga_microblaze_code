################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
first_hello_world_fpga_micro_blaze.elf.size \

ELFCHECK += \
first_hello_world_fpga_micro_blaze.elf.elfcheck \


# All Target
all: first_hello_world_fpga_micro_blaze.elf secondary-outputs

# Tool invocations
first_hello_world_fpga_micro_blaze.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze g++ linker'
	mb-g++ -Wl,-T -Wl,../src/lscript.ld -L../../first_hello_world_fpga_micro_blaze_bsp/microblaze_mcs_v1_4/lib -mlittle-endian -mcpu=v8.40.a -mxl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "first_hello_world_fpga_micro_blaze.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

first_hello_world_fpga_micro_blaze.elf.size: first_hello_world_fpga_micro_blaze.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size first_hello_world_fpga_micro_blaze.elf  |tee "first_hello_world_fpga_micro_blaze.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

first_hello_world_fpga_micro_blaze.elf.elfcheck: first_hello_world_fpga_micro_blaze.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck first_hello_world_fpga_micro_blaze.elf -hw ../../spartan_6_micro_blaze_/system.xml -pe microblaze_mcs_v1_4  |tee "first_hello_world_fpga_micro_blaze.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(ELFSIZE)$(CXX_DEPS)$(C_UPPER_DEPS)$(ELFCHECK)$(S_UPPER_DEPS) first_hello_world_fpga_micro_blaze.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
