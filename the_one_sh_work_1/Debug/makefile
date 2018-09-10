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
the_one_sh_work_1.elf.size \

ELFCHECK += \
the_one_sh_work_1.elf.elfcheck \


# All Target
all: the_one_sh_work_1.elf secondary-outputs

# Tool invocations
the_one_sh_work_1.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../the_one_sh_work_1_bsp/microblaze_0/lib -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "the_one_sh_work_1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

the_one_sh_work_1.elf.size: the_one_sh_work_1.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size the_one_sh_work_1.elf  |tee "the_one_sh_work_1.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

the_one_sh_work_1.elf.elfcheck: the_one_sh_work_1.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck the_one_sh_work_1.elf -hw ../../the_one_that_shoud_work_1/system.xml -pe microblaze_0  |tee "the_one_sh_work_1.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) the_one_sh_work_1.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
