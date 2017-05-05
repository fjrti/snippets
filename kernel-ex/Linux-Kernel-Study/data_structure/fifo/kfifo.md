# kfifo Lab

* 1 . Create a kernel module to test `kfifo`

* 2 . Use `kfifo_alloc` to init a kfifo.
```
ret = kfifo_alloc(&fifo, 4 * sizeof(struct student), GFP_KERNEL);
```

* 3 . Use `kfifo_in` to push data into kfifo's back
```
kfifo_in(&fifo, (char *)stu1, sizeof(struct student));
```

* 4 . Use `kifo_out` to pull data from kfifo's forward
```
kfifo_out(&fifo, c_tmp, sizeof(struct student));
```

* 5 . Use `kfifo_free` to free kfifo
```
kfifo_free(&fifo);
```

## Attention
Makefile
```
# we want `fifo.ko`
obj-m += fifo.o 
# fifo.o needs `kn_common.o` `testfifo.o`
fifo-objs := kn_common.o testfifo.o  
```
