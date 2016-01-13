################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
configPkg/compiler.opt: ../8core-BBT.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"D:/TInew/xdctools_3_23_03_53/xs" --xdcpath="D:/TInew/ipc_1_24_03_32/packages;D:/TInew/bios_6_33_06_50/packages;D:/TInew/pdk_C6678_1_1_2_6/packages;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p ti.platforms.evm6678 -r release -b "D:/HW_8CORE_BBT/8core-BBT_Nov_12_final/.config/xconfig_loopbackDioIsr/config.bld" -c "D:/TInew/ccsv5/tools/compiler/c6000_7.3.4" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: D:/HW_8CORE_BBT/8core-BBT_Nov_12_final/.config/xconfig_loopbackDioIsr/config.bld
configPkg/linker.cmd: configPkg/compiler.opt D:/HW_8CORE_BBT/8core-BBT_Nov_12_final/.config/xconfig_loopbackDioIsr/config.bld
configPkg/: configPkg/compiler.opt D:/HW_8CORE_BBT/8core-BBT_Nov_12_final/.config/xconfig_loopbackDioIsr/config.bld


