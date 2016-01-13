################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../platform_utils.cmd 

CFG_SRCS += \
../8core-BBT.cfg 

GEN_SRCS += \
./configPkg/compiler.opt \
./configPkg/linker.cmd 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_SRCS__QUOTED += \
"configPkg\compiler.opt" \
"configPkg\linker.cmd" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

CFG_SRCS__QUOTED += \
"../8core-BBT.cfg" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 


