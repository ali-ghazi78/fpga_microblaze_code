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
;;;.elf.size \

ELFCHECK += \
;;;.elf.elfcheck \


# All Target
all: ;;;.elf secondary-outputs

# Tool invocations
;;;.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../;;;_bsp/microblaze_mcs_v1_4/lib -mlittle-endian -mcpu=v8.40.a -mxl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o ";;;.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

;;;.elf.size: ;;;.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size ;;;.elf  |tee ";;;.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

;;;.elf.elfcheck: ;;;.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck ;;;.elf -hw ../../llll/system.xml -pe microblaze_mcs_v1_4  |tee ";;;.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) ;;;.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
