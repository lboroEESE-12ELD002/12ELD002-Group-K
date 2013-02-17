################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
../driver/ez430_chronos_drivers.lib 

C_SRCS += \
../driver/ports.c \
../driver/timer.c 

OBJS += \
./driver/ports.obj \
./driver/timer.obj 

C_DEPS += \
./driver/ports.pp \
./driver/timer.pp 

OBJS__QTD += \
".\driver\ports.obj" \
".\driver\timer.obj" 

C_DEPS__QTD += \
".\driver\ports.pp" \
".\driver\timer.pp" 

C_SRCS_QUOTED += \
"../driver/ports.c" \
"../driver/timer.c" 


# Each subdirectory must supply rules for building sources it contributes
driver/ports.obj: ../driver/ports.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/bin/cl430" --silicon_version=mspx -g -O2 --define=__CCE__ --define=ISM_US --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/msp430/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/include" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/include" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/driver" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/logic" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/bluerobin" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/simpliciti" --diag_warning=225 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/ports.pp" --obj_directory="driver" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

driver/timer.obj: ../driver/timer.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/bin/cl430" --silicon_version=mspx -g -O2 --define=__CCE__ --define=ISM_US --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/msp430/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/msp430/include" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/include" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/driver" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/logic" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/bluerobin" --include_path="C:/Program Files (x86)/Texas Instruments/eZ430-Chronos/Software Projects/Chronos Watch/CCS/Sports Watch/simpliciti" --diag_warning=225 --call_assumptions=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/timer.pp" --obj_directory="driver" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


