
all:
	gcc -c -fPIC ./lib/st1.c ./lib/st2.c
	ar -rsv libtest.a st1.o st2.o
	gcc -shared -fPIC -o libtest_d.so st1.o st2.o
	gcc -o test-a main.c -L./ -ltest
	gcc -o test-so main.c -L./ -ltest_d
	gcc -o test-dl main-dload.c -rdynamic -ldl

clean:
	rm -rf *.a *.o *.a *.so test-*	
	
	



