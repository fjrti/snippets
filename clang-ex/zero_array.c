#include <stdio.h>
#include <malloc.h>


typedef struct
{
	int version;
	int numFds;
	int numInts;
	int data[0];
} native_handle_t;

int main()
{
	int numFds = 2;
	int numInts = 0;

	native_handle_t* h = malloc(
		sizeof(native_handle_t) + sizeof(int)*(numFds+numInts));


	h->data[0] = 33;
	h->data[9] = 87;
	printf("sizeof zero array: %d %d\n",
			sizeof(*h), sizeof(native_handle_t));
	printf("%d %d\n", h->data[0], h->data[9]);

	return 0;
}
