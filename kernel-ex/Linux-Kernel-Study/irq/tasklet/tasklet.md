# Tasklet Lab

* 1. Use macro `DECLARE_TASKLET` to init a `struct tasklet_struct`
```
	DECLARE_TASKLET(mytasklet, my_tasklet_func, 1000);
```

* 2. Use function `tasklet_schedule` to schedule to let kernel run the function
```
	tasklet_schedule(&mytasklet);
```