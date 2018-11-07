################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MAX31855.obj: ../MAX31855.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/TI/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="C:/TI/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="{SW_ROOT}" --include_path="{SW_ROOT}/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/utils" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/include" --include_path="C:/Users/u10v29/workspace_v8/OfenLuefterSteuerung_MAX31855" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="MAX31855.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

S900_Inverter.obj: ../S900_Inverter.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/TI/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="C:/TI/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="{SW_ROOT}" --include_path="{SW_ROOT}/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/utils" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/include" --include_path="C:/Users/u10v29/workspace_v8/OfenLuefterSteuerung_MAX31855" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="S900_Inverter.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/TI/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="C:/TI/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="{SW_ROOT}" --include_path="{SW_ROOT}/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/utils" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/include" --include_path="C:/Users/u10v29/workspace_v8/OfenLuefterSteuerung_MAX31855" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

pinout.obj: ../pinout.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/TI/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="C:/TI/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="{SW_ROOT}" --include_path="{SW_ROOT}/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/utils" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/include" --include_path="C:/Users/u10v29/workspace_v8/OfenLuefterSteuerung_MAX31855" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="pinout.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tm4c123gh6pm_startup_ccs.obj: ../tm4c123gh6pm_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/TI/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="C:/TI/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="{SW_ROOT}" --include_path="{SW_ROOT}/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/utils" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/include" --include_path="C:/Users/u10v29/workspace_v8/OfenLuefterSteuerung_MAX31855" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="tm4c123gh6pm_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uartstdio.obj: C:/TI/TivaWare_C_Series-2.1.4.178/utils/uartstdio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/TI/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="C:/TI/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="{SW_ROOT}" --include_path="{SW_ROOT}/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/utils" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/include" --include_path="C:/Users/u10v29/workspace_v8/OfenLuefterSteuerung_MAX31855" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="uartstdio.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ustdlib.obj: C:/TI/TivaWare_C_Series-2.1.4.178/utils/ustdlib.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="C:/TI/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="C:/TI/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="{SW_ROOT}" --include_path="{SW_ROOT}/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/inc" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/utils" --include_path="C:/ti/TivaWare_C_Series-2.1.3.156/driverlib" --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_16.12.0.STS/include" --include_path="C:/Users/u10v29/workspace_v8/OfenLuefterSteuerung_MAX31855" --define=ccs="ccs" --define=PART_TM4C123GH6PM --gcc --abi=eabi --preproc_with_compile --preproc_dependency="ustdlib.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


