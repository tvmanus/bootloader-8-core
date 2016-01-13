#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/PROGRA~1/TEXASI~1/ipc_1_24_00_16/packages;D:/PROGRA~1/TEXASI~1/bios_6_32_05_54/packages;D:/PROGRA~1/TEXASI~1/pdk_C6678_1_0_0_17/packages;D:/workspace_v5_2/8core-BBT/.config
override XDCROOT = D:/PROGRA~1/TEXASI~1/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/PROGRA~1/TEXASI~1/ipc_1_24_00_16/packages;D:/PROGRA~1/TEXASI~1/bios_6_32_05_54/packages;D:/PROGRA~1/TEXASI~1/pdk_C6678_1_0_0_17/packages;D:/workspace_v5_2/8core-BBT/.config;D:/PROGRA~1/TEXASI~1/xdctools_3_23_03_53/packages;..
HOSTOS = Windows
endif
