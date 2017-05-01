/*
 * gcc -c bss.c
 * file bss.o
 * bss.o: ELF 32-bit LSB relocatable, Intel 80386, version 1 (SYSV), not stripped
 *
 *
 * nm bss.o
 *
 * 00000000 B a
 * 00000008 D arr
 * 00000004 C array
 * 00000004 D b
 * 00000008 b i
 * 00000000 d j
 * 00000014 d l.1711 static local variable has this extention?????
 * 00000000 T main
 * 00000010 d p0.1712
 * 0000000c b p1.1713
 * 00000004 B sp
 *
 *
 * objdump -h bss.o
 *
 * bss.o:     file format elf32-i386
 *
 * Sections:
 * Idx Name          Size      VMA       LMA       File off  Algn
 *   0 .text         00000021  00000000  00000000  00000034  2**2
 *                   CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
 *   1 .data         00000018  00000000  00000000  00000058  2**2
 *                   CONTENTS, ALLOC, LOAD, RELOC, DATA
 *   2 .bss          00000010  00000000  00000000  00000070  2**2
 *                   ALLOC
 *   3 .rodata       0000000c  00000000  00000000  00000070  2**0
 *                   CONTENTS, ALLOC, LOAD, READONLY, DATA
 *   4 .comment      00000024  00000000  00000000  0000007c  2**0
 *                   CONTENTS, READONLY
 *   5 .note.GNU-stack 00000000  00000000  00000000  000000a0  2**0
 *                   CONTENTS, READONLY
 */

#include <stdio.h>

static int i = 0;	/* b: bss section  */
int a = 0;		/* B: bss section  */
char *sp = NULL;	/* B: bss section  */

static int j = 1;	/* d: data section */
int b = 1;		/* D: data section */
int arr[2] = {1, 2};	/* D: data section */

int *array;	/* C:  */

int main()
{
	char s[] = "hello";	/* s is on stack, "hello" .text?? */
	char *p = "world";	/* p is on stack, "world" .rodata
				 * and is allocated at build time */
	int k;			/* on stack */
	static int l = 87;	/* d: data section */
	static char *p0 = "happy";	/* d: data section, "happy" .rodata */

	static char *p1 = NULL;	/* b: bss section */

	/* s: 0xbfc1a0d2, p: 0x80484f0, k: 0xbfc1a0d8 */
	/* cat /proc/15670/maps */
	/* bfc07000-bfc1c000 rw-p 00000000 00:00 0          [stack] */
	printf("s: %p, p: %p, k: %p\n", s, p, &k);

	//while (1);

	return 0;
}
