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
7_vali_ba_6.elf.size \

ELFCHECK += \
7_vali_ba_6.elf.elfcheck \


# All Target
all: 7_vali_ba_6.elf secondary-outputs

# Tool invocations
7_vali_ba_6.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze gcc linker'
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../7_vali_ba_6_bsp/microblaze_0/lib -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -Wl,--gc-sections -o "7_vali_ba_6.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

7_vali_ba_6.elf.size: 7_vali_ba_6.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size 7_vali_ba_6.elf  |tee "7_vali_ba_6.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

7_vali_ba_6.elf.elfcheck: 7_vali_ba_6.elf
	@echo 'Invoking: Xilinx ELF Check'
	elfcheck 7_vali_ba_6.elf -hw ../../6_board/system.xml -pe microblaze_0  |tee "7_vali_ba_6.elf.elfcheck"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) 7_vali_ba_6.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
