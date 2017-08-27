all:
	gcc -Wall -I.  -O2 -DENABLE_POLL -DENABLE_EPOLL -DENABLE_SPLICE -DENABLE_ACCEPT4  -DSTATTIME=0 -g -c -static -o httpterm.o httpterm.c

clean:
	rm -f *.[oas] *~ *.rej core httpterm test nohup.out gmon.out
	rm -f httpterm-$(VERSION).tar.gz httpterm-$(VERSION)
