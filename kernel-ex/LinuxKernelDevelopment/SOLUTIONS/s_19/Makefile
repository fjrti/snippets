### Automatic Makefile generation by 'genmake' script        ####
### Copyright, Jerry Cooperstein, coop@linuxfoundation.org 2/2003 - 1/2016 ####
### License: GPLv2 ###

allofit:  userprogs

userprogs:
	@$(MAKE) \
		CFLAGS="-O2 -Wall -pedantic -pthread" \
		LDLIBS="-L /usr/local/lib64 -lhugetlbfs" \
	 lab1_hugepage_mm lab2_hugepage_shm lab3_hugewaste lab3_wastemem

clean:
	rm -rf  lab1_hugepage_mm lab2_hugepage_shm lab3_hugewaste lab3_wastemem 
