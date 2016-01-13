################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/TInew/ccsv5/tools/compiler/c6000_7.3.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./src/srioloopback.obj" \
"./src/srio_device_config.obj" \
"./src/spi_nor.obj" \
"./src/spi_fpga.obj" \
"./src/spi.obj" \
"./src/qmss_device.obj" \
"./src/platforms_utils_test.obj" \
"./src/platform.obj" \
"./src/loopbackDioIsr_osal.obj" \
"./src/interrupt.obj" \
"./src/evmc66x_uart.obj" \
"./src/evmc66x_nor.obj" \
"./src/evmc66x_i2c_eeprom.obj" \
"./src/evmc66x_gpio.obj" \
"./src/evmc66x_fpga.obj" \
"./src/evmc6678_phy.obj" \
"./src/evmc6678.obj" \
"./src/evm66x_nand.obj" \
"./src/evm66x_i2c.obj" \
"./src/cppi_device.obj" \
"./src/bbt_osal.obj" \
"./src/bbt.obj" \
"./src/Test_bbt.obj" \
-lti.csl.ae66 \
-lti.csl.intc.ae66 \
-l"libc.a" \
"../platform_utils.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: 8core-BBT.out

# Tool invocations
8core-BBT.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6600 -g --diag_warning=225 --abi=eabi -z -m"8core-BBT.map" --warn_sections -i"D:/TInew/ccsv5/tools/compiler/c6000_7.3.4/lib" -i"D:/TInew/ccsv5/tools/compiler/c6000_7.3.4/include" -i"D:/Program Files (x86)/Texas Instruments/pdk_C6678_1_1_2_6/packages/ti/drv/srio/lib" -i"D:/Program Files (x86)/Texas Instruments/pdk_C6678_1_1_2_6/packages/ti/csl/lib" --reread_libs --rom_model -o "8core-BBT.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_SRCS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(C6000_EXECUTABLE_OUTPUTS__QUOTED)$(GEN_OPTS__QUOTED)$(GEN_CMDS__QUOTED) "8core-BBT.out"
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-$(RM) "src\Test_bbt.pp" "src\bbt.pp" "src\bbt_osal.pp" "src\cppi_device.pp" "src\evm66x_i2c.pp" "src\evm66x_nand.pp" "src\evmc6678.pp" "src\evmc6678_phy.pp" "src\evmc66x_fpga.pp" "src\evmc66x_gpio.pp" "src\evmc66x_i2c_eeprom.pp" "src\evmc66x_nor.pp" "src\evmc66x_uart.pp" "src\interrupt.pp" "src\loopbackDioIsr_osal.pp" "src\platform.pp" "src\platforms_utils_test.pp" "src\qmss_device.pp" "src\spi.pp" "src\spi_fpga.pp" "src\spi_nor.pp" "src\srio_device_config.pp" "src\srioloopback.pp" 
	-$(RM) "src\Test_bbt.obj" "src\bbt.obj" "src\bbt_osal.obj" "src\cppi_device.obj" "src\evm66x_i2c.obj" "src\evm66x_nand.obj" "src\evmc6678.obj" "src\evmc6678_phy.obj" "src\evmc66x_fpga.obj" "src\evmc66x_gpio.obj" "src\evmc66x_i2c_eeprom.obj" "src\evmc66x_nor.obj" "src\evmc66x_uart.obj" "src\interrupt.obj" "src\loopbackDioIsr_osal.obj" "src\platform.obj" "src\platforms_utils_test.obj" "src\qmss_device.obj" "src\spi.obj" "src\spi_fpga.obj" "src\spi_nor.obj" "src\srio_device_config.obj" "src\srioloopback.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
