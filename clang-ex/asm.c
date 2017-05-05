/*
 * Refer See MIPS run second editon(Section 10.5, page 306) for more
 *
 *     The function itself is declared inline, which instructs the compiler that
 *  a use of this function should be replaced by a copy of its logic (which
 *  permits local register optimization to apply). Adding static means that
 *  the function need not be published for other modules to use, so no binary
 *  of the function itself will be generated. It very often makes sense to wrap
 *  an asm() like this: You’d probably usually then put the whole definition
 *  in an include file. You could use a C preprocessor macro, but the inlined
 *  function is a bit cleaner.
 *      The declarations inside the asm() parentheses tell GCC to emit a MIPS mul
 *  line to the assembler with three operands on the command line—one will be the
 *  output and two will be inputs.
 *      On the line below, we tell GCC about operand %0, the product: first, that this
 *  value will be write-only (meaning that there’s no need to preserve its original
 *  value) with the “=” modifier; the “r” tells GCC that it’s free to choose any of
 *  the general-purpose registers to hold this value. Finally, we tell GCC that the
 *  operand we wrote as %0 corresponds to the C variable p.
 *      On the third line of the asm() construct, we tell GCC about operands %1
 *  and %2. Again, we allow GCC to put these in any of the general-purpose registers,
 *  and tell it that they correspond to the C variables a and b.
 *      At the end of the example function, the result we obtained from the multiply
 *  instruction is returned to the C caller.
 *      GCC allows considerable control over the specification of the operands; you
 *  can tell it that certain values are both read and written and that certain hardware *   registers are left with meaningless values as a side effect of a particular assembly
 *  sequence. You can dig out the details from the MIPS-specific sections of the GCC
 *  manual.
 */

/*
 * NOTE: this may only works on mips architecture, other platforms are not guaranteed
 */

#include <stdio.h>

static int __inline__ mymul(int a, int b)
{
	int p;

	asm("mul %0, %1, %2"
		: "=r" (p)
		: "r" (a), "r" (b)
	);

	return p;
}

int main()
{
	int i = 2, j = 3;

	printf("i * j = %d\n", mymul(i, j));

	return 0;
}
