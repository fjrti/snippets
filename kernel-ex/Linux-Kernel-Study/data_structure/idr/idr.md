# idr lab

**Attention: we use kernel whose version is 3.18.44. So the functions in 2.16.x not necessarily work**

* 1. Use the macro `DEFINE_IDR` to allocate a new `struct idr`
```
	DEFINE_IDR(idp);
```

* 2. Init the self-definition struction array
```
	for(i = 0; i < 4; i++){
    	stu[i] = kmalloc(sizeof(struct student), GFP_KERNEL);
    	stu[i]->id = i;
    	stu[i]->name = "xr_nku";
    }
```

* 3. Use the code pattern in the source code(idr.c) to allocate a new UID for each structure
```
	idr_preload(GFP_KERNEL);


	ret = idr_alloc(&idp, stu[i], 1, -1, GFP_KERNEL);

	idr_preload_end();
		
	if(ret < 0)
		error
```

* 4. Iterate the `struct idr` for all UIDs and its corresponding pointers.
```
	idr_for_each(&idp, print_student, NULL);
```

* 5. destroy the `struct idr`
```
	idr_destroy(&idp);
```
