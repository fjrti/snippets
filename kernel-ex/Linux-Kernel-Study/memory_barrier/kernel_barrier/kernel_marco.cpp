// g++ -O2 -S kernel_marco.cpp
int x, y, r;
#define ACCESS_ONCE(x) (*(volatile typeof(x) *)&(x))
void f(){
	ACCESS_ONCE(x) = r;
    ACCESS_ONCE(y) = 1;
}