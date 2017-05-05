# This code piece is using `struct list_head` for kernel module.
## Some stupid mistakes
* 1. The target and source should have same name.

## install the kernel module
```
insmod testlist.ko
rmmod testlist
dmesg | tail -100
```
