#define NO_BIT_DEFINES
#include <pic14regs.h>
#include <stdint.h> 

static __code uint16_t __at (_CONFIG) __configword =
    _FOSC_HS & _WDTE_OFF & _LVP_OFF & _WRT_OFF & _BOREN_OFF;

#define LED_PORT PORTBbits.RB0
#define LED_TRIS TRISBbits.TRISB0

#define _XTAL_FREQ 16000000

void
delay(uint16_t iter)
{
	uint16_t i;

	for (i = 0; i < iter; i++)
		__asm nop __endasm;
}

void main(void)
{
	LED_TRIS = 0; /* Pin as output */
	LED_PORT = 0; /* LED off */
	
	while (1) {
		LED_PORT = 1; /* LED on */
		delay(30000); /* ~500ms @ 4MHz */
		LED_PORT = 0; /* LED off */
		delay(30000);
	}
}
