################################################################################
# Automatically-generated file. Do not edit!
################################################################################

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./driver/timer.obj" \
"./driver/ports.obj" \
"./logic/user.obj" \
"./logic/test.obj" \
"./logic/temperature.obj" \
"./logic/stopwatch.obj" \
"./logic/rfsimpliciti.obj" \
"./logic/rfbsl.obj" \
"./logic/menu.obj" \
"./logic/date.obj" \
"./logic/clock.obj" \
"./logic/bluerobin.obj" \
"./logic/battery.obj" \
"./logic/altitude.obj" \
"./logic/alarm.obj" \
"./logic/acceleration.obj" \
"./logic/Eggtimer.obj" \
"./main.obj" \
-l"rts430x.lib" \
"../simpliciti/CC430_End_Device_915MHz.lib" \
"../lnk_cc430f6137.cmd" \
"../driver/ez430_chronos_drivers.lib" \
"../bluerobin/BlueRobin_RX_915MHz.lib" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include simpliciti/subdir.mk
-include logic/subdir.mk
-include driver/subdir.mk
-include bluerobin/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ez430_chronos_915MHz.out

# Tool invocations
ez430_chronos_915MHz.out: $(GEN_CMDS) $(CMD_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(shell echo --silicon_version=mspx > ccsLinker.opt)
	$(shell echo -g >> ccsLinker.opt)
	$(shell echo -O2 >> ccsLinker.opt)
	$(shell echo --define=__CCE__ --define=ISM_US >> ccsLinker.opt)
	$(shell echo --diag_warning=225 >> ccsLinker.opt)
	$(shell echo --call_assumptions=0 >> ccsLinker.opt)
	$(shell echo --gen_opt_info=2 >> ccsLinker.opt)
	$(shell echo --printf_support=minimal >> ccsLinker.opt)
	$(shell echo -z >> ccsLinker.opt)
	$(shell echo -m"ez430_chronos.map" >> ccsLinker.opt)
	$(shell echo --stack_size=80 >> ccsLinker.opt)
	$(shell echo --heap_size=80 >> ccsLinker.opt)
	$(shell echo --use_hw_mpy=F5 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"C:/Program Files (x86)/Texas Instruments/ccsv4/msp430/include" -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/lib" -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/include" >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/bin/cl430" -@ccsLinker.opt -o "ez430_chronos_915MHz.out"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(S62_DEPS__QTD)$(OBJS__QTD)$(C64_DEPS__QTD)$(ASM_DEPS__QTD)$(C62_DEPS__QTD)$(C_UPPER_DEPS__QTD)$(S??_DEPS__QTD)$(S55_DEPS__QTD)$(S64_DEPS__QTD)$(C55_DEPS__QTD)$(C67_DEPS__QTD)$(CPP_DEPS__QTD)$(C43_DEPS__QTD)$(C_DEPS__QTD)$(S43_DEPS__QTD)$(CC_DEPS__QTD)$(MSP430_EXECUTABLE_OUTPUTS__QTD)$(S67_DEPS__QTD)$(OPT_DEPS__QTD)$(S_UPPER_DEPS__QTD)$(C??_DEPS__QTD)$(CXX_DEPS__QTD)$(C++_DEPS__QTD)$(S_DEPS__QTD)$(SA_DEPS__QTD)$(ASM_UPPER_DEPS__QTD) "ez430_chronos_915MHz.out"
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/bin/hex430.exe" --ti_txt "ez430_chronos_915MHz.out" -o "ez430_chronos_915MHz.txt" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
