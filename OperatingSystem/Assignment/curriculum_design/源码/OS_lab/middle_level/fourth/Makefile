obj-m:=lumosdev.o
CURRENT_PATH:=$(shell pwd)
CONFIG_MODULE_SIG=n
LINUX_KERNEL_PATH:=/usr/src/linux-headers-5.19.0-38-generic
all:
	make -C  $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C  $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
