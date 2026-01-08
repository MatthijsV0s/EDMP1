################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
driverlib/MSP430FR5xx_6xx/%.obj: ../driverlib/MSP430FR5xx_6xx/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccs2040/ccs/ccs_base/msp430/include" --include_path="C:/Users/matth/Firmware/EDMP1/lab_07c_initPorts_solution_msp430fr5969/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power="none" --advice:hw_config=all -g --define=__MSP430FR5969__ --display_error_number --diag_wrap=off --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="driverlib/MSP430FR5xx_6xx/$(basename $(<F)).d_raw" --obj_directory="driverlib/MSP430FR5xx_6xx" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


