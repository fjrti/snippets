// g++ -O2 -S kernel_barrier.cpp
int x, y, r;

void f(){
	x = r;
	__asm__ __volatile__("" ::: "memory");
	y = 1;
}