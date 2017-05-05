// gcc -o sys_test test_new_syscall.c -m32
#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/types.h>
#include <time.h>

void sys_call_use_function();
void sys_call_use_int();
void sys_call_uname();
void sys_call_uname_int();

int main(){
	printf("syscall use function syscall()\n");
	sys_call_use_function();
	sys_call_use_int();
	sys_call_uname();
	sys_call_uname_int();
	return 0;
}

void sys_call_use_function(){
	printf("#########################Use function syscall()###########################\n");
	long ID1,ID2;
	ID1 = syscall(322);
	printf("syscall(SYS_foo): %ld\n", ID1);
	ID2 = getpid();
	printf("getpid(): %ld\n", ID2);
	time_t tt;
	struct tm *t;
	tt = time(NULL);
	t = localtime(&tt);
	printf("time():time:%d:%d:%d:%d:%d:%d\n", t->tm_year+1900,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
}

void sys_call_use_int(){
	printf("#########################Use int $0x80 (0x166, 0xd)###########################\n");
	long ID1;
	asm volatile(
		"mov $0x166,%%eax\n\t"
		"int $0x80\n\t"
		"mov %%eax, %0\n\t"
		:"=m"(ID1)
	);
	printf("(int $0x80) pid: %ld\n", ID1);
	time_t tt;
	struct tm *t;
	asm volatile(
		"mov $0,%%ebx\n\t"
		"mov $0xd,%%eax\n\t"
		"int $0x80\n\t"
		"mov %%eax,%0\n\t"
		:"=m"(tt)
	);
	t = localtime(&tt);
	printf("(int $0x80)time:%d:%d:%d:%d:%d:%d\n", t->tm_year+1900,t->tm_mon,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
}

void sys_call_uname(){
	printf("#########################Use funtion uname()###########################\n");
	struct utsname buf;
	struct utsname *p = &buf;
	uname(p);
	printf("sysname:%s\nnodename:%s\nrelease:%s\nversion:%s\nmachine:%s\n", \
		buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
}
	
void sys_call_uname_int(){
	printf("#########################Use int &0x80 (0x7a)###########################\n");
	struct utsname buf;
	struct utsname *p = &buf;
	int res;
	asm volatile(
		"mov %1, %%ebx\n\t"
		"mov $0x7a, %%eax\n\t"
		"int $0x80\n\t"
		"mov %%eax, %0\n\t"
		:"=m"(res)
		:"b"(p)
	);
	printf("sysname:%s\nnodename:%s\nrelease:%s\nversion:%s\nmachine:%s\n", \
		buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
}

