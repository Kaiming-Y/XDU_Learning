cmd_/home/lumos/OS_lab/low_level/third/modules.order := {   echo /home/lumos/OS_lab/low_level/third/my_system.ko; :; } | awk '!x[$$0]++' - > /home/lumos/OS_lab/low_level/third/modules.order
