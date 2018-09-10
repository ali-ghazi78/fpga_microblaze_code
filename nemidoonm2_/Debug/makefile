################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/src/subdir.mk
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
nemidoonm2_.elf.size \

ELFCHECK += \
nemidoonm2_.elf.elfcheck \


# All Target
all: nemidoonm2_.elf secondary-outputs

# Tool invocations
nemidoonm2_.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../nemidoonm2__bsp/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "nemidoonm2_.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

nemidoonm2_.elf.size: nemidoonm2_.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size nemidoonm2_.elf  |tee "nemidoonm2_.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

nemidoonm2_.elf.elfcheck: nemidoonm2_.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck nemidoonm2_.elf -hw ../../nemidonm2/system.xml -pe microblaze_0  |tee "nemidoonm2_.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) nemidoonm2_.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
