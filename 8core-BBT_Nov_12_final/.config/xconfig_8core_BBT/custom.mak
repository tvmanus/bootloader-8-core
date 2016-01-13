## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd \
  package/cfg/8core-BBT_pe66.oe66 \

linker.cmd: package/cfg/8core-BBT_pe66.xdl
	$(SED) 's"^\"\(package/cfg/8core-BBT_pe66cfg.cmd\)\"$""\"D:/workspace_v5_2/8core-BBT/.config/xconfig_8core_BBT/\1\""' package/cfg/8core-BBT_pe66.xdl > $@
