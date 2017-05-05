### Automatic Makefile generation by 'genmake' script        ####
### Copyright, Jerry Cooperstein, coop@linuxfoundation.org 2/2003 - 1/2016 ####
### License: GPLv2 ###

obj-m +=  lab1_cache.o lab2_mempool.o lab3_maxmem.o lab3_maxvmalloc.o

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
	 lab3_wastemem

clean: kernel_clean
	rm -rf  lab3_wastemem  Module.symvers modules.order
