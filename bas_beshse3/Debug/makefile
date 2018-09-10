################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/my_lib/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
bas_beshse3.elf.size \

ELFCHECK += \
bas_beshse3.elf.elfcheck \


# All Target
all: bas_beshse3.elf secondary-outputs

# Tool invocations
bas_beshse3.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../bas_beshse3_bsp/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "bas_beshse3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

bas_beshse3.elf.size: bas_beshse3.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size bas_beshse3.elf  |tee "bas_beshse3.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

bas_beshse3.elf.elfcheck: bas_beshse3.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck bas_beshse3.elf -hw ../../bas_beshe3/system.xml -pe microblaze_0  |tee "bas_beshse3.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) bas_beshse3.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
