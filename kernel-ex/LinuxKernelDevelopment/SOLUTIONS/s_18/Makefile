### Automatic Makefile generation by 'genmake' script        ####
### Copyright, Jerry Cooperstein, coop@linuxfoundation.org 2/2003 - 1/2016 ####
### License: GPLv2 ###

obj-m +=  lab1_allpages.o
obj-m +=  lab1_x.o

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
	 lab2_devmemkmem

clean: kernel_clean
	rm -rf  lab2_devmemkmem  Module.symvers modules.order
