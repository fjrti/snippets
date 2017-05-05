obj-m += tasklet.o
tasklet-objs := testtasklet.o kn_common.o

CURRENT_PATH := $(shell pwd)

LINUX_KERNEL := $(shell uname -r)

LINUX_KERNEL_PATH := /lib/modules/$(LINUX_KERNEL)/build

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
	rm -rf modules.order Module.symvers .*.cmd *.o *.mod.c .tmp_versions *.unsigned

clean:
	rm -rf modules.order Module.symvers .*.cmd *.o *.mod.c *.ko .tmp_versions *.unsigned