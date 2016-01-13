## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd \
  package/cfg/8core-BBT_pe66.oe66 \

linker.cmd: package/cfg/8core-BBT_pe66.xdl
	$(SED) 's"^\"\(package/cfg/8core-BBT_pe66cfg.cmd\)\"$""\"D:/HW_8CORE_BBT/8core-BBT_Nov_12_final/Debug/configPkg/\1\""' package/cfg/8core-BBT_pe66.xdl > $@
