#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/TInew/ipc_1_24_03_32/packages;D:/TInew/bios_6_33_06_50/packages;D:/TInew/pdk_C6678_1_1_2_6/packages
override XDCROOT = D:/TInew/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/TInew/ipc_1_24_03_32/packages;D:/TInew/bios_6_33_06_50/packages;D:/TInew/pdk_C6678_1_1_2_6/packages;D:/TInew/xdctools_3_23_03_53/packages;..
HOSTOS = Windows
endif
