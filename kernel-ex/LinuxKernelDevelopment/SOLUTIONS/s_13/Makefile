### Automatic Makefile generation by 'genmake' script        ####
### Copyright, Jerry Cooperstein, coop@linuxfoundation.org 2/2003 - 1/2016 ####
### License: GPLv2 ###

obj-m +=  lab2_kthreads.o lab3_launch_cp.o lab3_launch_wall.o

export KROOT=/lib/modules/3.19.0-61-generic/build

allofit:  userprogs modules
modules:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) modules
modules_install:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) modules_install
kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) clean

userprogs:
	@$(MAKE) \
		CFLAGS="-O2 -Wall -pedantic -pthread" \
	 lab1_clone

clean: kernel_clean
	rm -rf  lab1_clone  Module.symvers modules.order
