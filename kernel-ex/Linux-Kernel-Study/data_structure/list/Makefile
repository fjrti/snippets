obj-m += testlist.o

# generate the path
CURRENT_PATH=$(shell pwd)

#the current kernel version number
LINUX_KERNEL=$(shell uname -r)

#the absolute path
LINUX_KERNEL_PATH:=/lib/modules/$(LINUX_KERNEL)/build

#compile object
all:
	make -C $(LINUX_KERNEL_PATH) SUBDIRS=$(CURRENT_PATH) modules

#clean
clean:
	rm -rf *.cmd *.d *.ko *.mod.c *.symvers *.order *.o

