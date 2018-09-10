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
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
bas_beshe_2code.elf.size \

ELFCHECK += \
bas_beshe_2code.elf.elfcheck \


# All Target
all: bas_beshe_2code.elf secondary-outputs

# Tool invocations
bas_beshe_2code.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../bas_beshe_2code_bsp/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "bas_beshe_2code.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

bas_beshe_2code.elf.size: bas_beshe_2code.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size bas_beshe_2code.elf  |tee "bas_beshe_2code.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

bas_beshe_2code.elf.elfcheck: bas_beshe_2code.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck bas_beshe_2code.elf -hw ../../bas_bashe_2/system.xml -pe microblaze_0  |tee "bas_beshe_2code.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) bas_beshe_2code.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
