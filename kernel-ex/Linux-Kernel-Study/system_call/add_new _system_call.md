# System Call

## Add new system call
* 1. open file `include/uapi/asm-generic/unistd.h`
* 2. update macro `__NR_syscalls` by plus 1(+1)
```
#undef __NR_syscalls
#define __NR_syscalls 282
```
* 3. create a new system call as forward items
```
#define __NR_foo 281
__SYSCALL(__NR_foo, sys_foo)
```
* 4. open file `arch/x86/syscall/syscall_32.tbl` and ``arch/x86/syscall/syscall_64.tbl``
```
# new system call
358	i386	foo			sys_foo
```
```
# new system call
322	common	foo			sys_foo
```
* 5. add system call implement in file `kernel/sys.c`
```
SYSCALL_DEFINE0(foo)
{
	return current->pid;
}
```
* 6. test new system call
```
ID1 = syscall(322);   // call new system call , the syscall number is 322
```

## Interrupt a syscall by `int`
* 1. system call number（eax）, arguments（ebx，ecx，edx，esi，edi，ebp）,get return(eax)
```
	asm volatile(
		"mov $0,%%ebx\n\t"
		"mov $0xd,%%eax\n\t"
		"int $0x80\n\t"
		"mov %%eax,%0\n\t"
		:"=m"(tt)
	);
```
`0xd` is 'sys_time' in `syscal_32.tbl`
* 2. Remember 'sys_time' call doesn't return the `utsname` struct, but a integer representing success or not.
The time result has already written to your buffer after the syscall. Don't destroy that buffer with other things.
* 3. Use '-m32' config to compile the file.
```
Maybe something fail in 64 bit machine:
use: sudo apt-get install libc6-dev-i386 
```
