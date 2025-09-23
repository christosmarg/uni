#define NO_BIT_DEFINES
#include <pic14regs.h>
#include <stdint.h> 
#include <string.h>

static __code uint16_t __at (_CONFIG) __configword =
    _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _LVP_OFF & _WRT_OFF & _BOREN_ON &
    _CPD_OFF & _CP_OFF;

#define _XTAL_FREQ 16000000
#define TIMER_INTERNAL_CLK (0 << 5)
#define TIMER_RISING_EDGE (0 << 4)
#define TIMER_PRESCALER_TMR0 (0 << 3)
/*
 * The last 3 bits of OPTION_REG indicate the prescalar value. In this case,
 * 111 indicates a prescalar value of 256.
 */
#define TIMER_PRESCALER_256 0b111
/* 
 * We want 1ms delay @ 16Mhz with 256 prescalar, the formula is:
 *
 * 256 - ((delay * (fosc / 1000)) / (prescalar * 4)) =
 * 256 - ((1 * (16000000 / 1000)) / (256 * 4)) =
 * 256 - ((1 * 16000) / (256 * 4)) =
 * 256 - 15.625 = ~240
 *
 * sdcc, there's no overflow here...
 */
#define TIMER_DELAY (256 - ((1 * (_XTAL_FREQ / 1000)) / (256 * 4)))
#define TIMER_REQ_MAX 3

#define LED1_PORT PORTBbits.RB0
#define LED1_TRIS TRISBbits.TRISB0

#define OUTPUT 0
#define INPUT 1

typedef void (*ev_handler)(void);

struct timer_req {
	ev_handler handler;
	uint32_t rate;
	uint32_t cnt;
};

static void	tmr0_init(void);
static int	tmr0_set_event(ev_handler, uint32_t);
static void	tmr0_isr(void) __interrupt;
static void	led_blink(void);

static struct timer_req reqs[TIMER_REQ_MAX];

void
tmr0_init(void)
{
	struct timer_req *r;
	uint8_t i;

	for (i = 0; i < TIMER_REQ_MAX; i++) {
		r = &reqs[i];
		r->handler = NULL;
		r->rate = 0;
		r->cnt = 0;
	}
	OPTION_REG = 0;
	OPTION_REG |= TIMER_INTERNAL_CLK | TIMER_RISING_EDGE |
	    TIMER_PRESCALER_TMR0 | TIMER_PRESCALER_256;
	TMR0 = TIMER_DELAY;
	/*
	 * Enable, TMR0 Interrupt Enable bit, Global Interrupt Enable bit
	 * and Peripheral Interrupt Enable bit.
	 */
	INTCONbits.TMR0IE = 1;
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
}

int
tmr0_set_event(ev_handler handler, uint32_t rate)
{
	struct timer_req *r;
	uint8_t i;

	for (i = 0; i < TIMER_REQ_MAX; i++) {
		r = &reqs[i];
		if (r->handler != NULL)
			continue;
		r->handler = handler;
		r->rate = rate;
		r->cnt = 0;
		return (1);
	}
	return (0);
}

void
tmr0_isr(void) __interrupt
{
	struct timer_req *r;
	uint8_t i;

	if (INTCONbits.TMR0IF != 1)
		return;
	for (i = 0; i < TIMER_REQ_MAX; i++) {
		r = &reqs[i];
		if (r->handler == NULL)
			continue;
		if (++r->cnt == r->rate) {
			r->handler();
			r->cnt = 0;
		}
	}
	TMR0 = TIMER_DELAY;
	INTCONbits.TMR0IF = 0;
}

void
led_blink(void)
{
	LED1_PORT ^= 1;
}

void
main(void)
{
	tmr0_init();
	tmr0_set_event(&led_blink, 1000); /* blink every 1 sec */

	LED1_TRIS = OUTPUT;
	LED1_PORT = 0; /* off */

	for (;;) {
	}
}
