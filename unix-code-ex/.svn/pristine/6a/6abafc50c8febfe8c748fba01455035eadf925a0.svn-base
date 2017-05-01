all: 
	gcc server/ae.c server/anet.c server/yhserver.c -O -g -ggdb -o tcp-server
	gcc client/client.c -O -g -ggdb -o tcp-client

clean: 
	-rm -rf tcp* server/*.o client/*.o

.PHONY: all clean
