LINUX_SRC =/lib/modules/$(shell uname -r)/build
obj-m := printk_test.o
all:
	make -C $(LINUX_SRC) SUBDIRS=$(shell pwd) modules   
clean:
	rm -rf *.cmd *.d *.ko *.mod.c *.symvers *.order *.o 