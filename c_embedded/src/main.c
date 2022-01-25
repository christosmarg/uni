#define NO_BIT_DEFINES
#include <pic14regs.h>
#include <stdint.h> 
#include <string.h>

static __code uint16_t __at (_CONFIG) __configword =
    _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _LVP_OFF & _WRT_OFF & _BOREN_ON &
    _CPD_OFF & _CP_OFF;

#define _XTAL_FREQ 16000000		/* Crystal oscillator running at 16MHz */
#define TIMER_RISING_EDGE (0 << 6)	/* Interrupt on rising edge */
#define TIMER_INTERNAL_CLK (0 << 5)	/* Use the CLK0 pin */
#define TIMER_PRESCALAR_TMR0 (0 << 3)	/* Assign prescalar to TMR0 */
/*
 * The last 3 bits of OPTION_REG indicate the prescalar value. In this case,
 * 111 indicates a prescalar value of 256.
 */
#define TIMER_PRESCALAR_256 0b111
/* 
 * We want 1ms delay @ 16Mhz with 256 prescalar, the formula is:
 *
 * 256 - ((delay * (fosc / 1000)) / (prescalar * 4)) =
 * 256 - ((1 * (16000000 / 1000)) / (256 * 4)) =
 * 256 - ((1 * 16000) / (256 * 4)) =
 * 256 - 15.625 = ~240
 *
 * sdcc thinks there's an overflow here (hint: he's wrong)...
 */
#define TIMER_DELAY (256 - ((1 * (_XTAL_FREQ / 1000)) / (256 * 4)))
#define TIMER_REQ_MAX 3

#define OUTPUT 0
#define INPUT 1

#define BTN_PORT PORTBbits.RB0
#define BTN_TRIS TRISBbits.TRISB0
#define BTN_DEBOUNCE_TIME_MS 20

#define LED_PORT PORTBbits.RB1
#define LED_TRIS TRISBbits.TRISB1

#define LCD_RS PORTCbits.RC0
#define LCD_RW PORTCbits.RC1
#define LCD_EN PORTCbits.RC2
#define LCD_PORT_DATA PORTD
#define LCD_SEL_INST 0
#define LCD_SEL_DATA 1
#define LCD_CLEAR 0x01		/* Clear screen */
#define LCD_CURS_ZERO 0x02	/* Set cursor on (0, 0) */
#define LCD_CURS_INC 0x06	/* Auto-increment cursor */
#define LCD_CURS_OFF 0x0c	/* Hide cursor */
#define LCD_MODE 0x38		/* 16x2 setup */
#define LCD_DISPLAY_INIT 0x32	/* Required */
/* Function macros */
#define lcd_putc(c) lcd_data(c, LCD_SEL_DATA)
#define lcd_cmd(cmd) lcd_data(cmd, LCD_SEL_INST)

typedef void (*ev_handler)(void);

struct timer_req {
	ev_handler handler;
	uint32_t rate;
	uint32_t cnt;
};

static void	delay_ms(uint32_t);
static void	tmr0_init(void);
static int	tmr0_set_event(ev_handler, uint32_t);
static void	tmr0_isr(void) __interrupt;
static void	led_blink(void);
static void	button_debounce(void);
static void	lcd_init(void);
static void	lcd_data(uint8_t, uint8_t);
static void	lcd_puts(const char *);

static struct timer_req reqs[TIMER_REQ_MAX];
static uint32_t timecnt = 0; /* Seconds passed since start */

static void
delay_ms(uint32_t t)
{
	while (t--)
		__asm nop __endasm;
}

static void
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
	    TIMER_PRESCALAR_TMR0 | TIMER_PRESCALAR_256;
	TMR0 = TIMER_DELAY;
	INTCONbits.TMR0IE = 1;	/* TMR0 Interrupt Enable */
	INTCONbits.GIE = 1;	/* Global Interrupt Enable */
	INTCONbits.PEIE = 1;	/* Peripheral Interrupt Enable */
}

static int
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

static void
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
	INTCONbits.TMR0IF = 0; /* Clear interrupt flags */
}

static void
led_blink(void)
{
	LED_PORT ^= 1;
	/*
	 * Increment here since this function is called every 1 sec.
	 * No need to create another one.
	 */
	timecnt++;
}


static void
button_debounce(void)
{
	static uint16_t cnt = 0;

	/* Button is pressed */
	if (BTN_PORT == 0) {
		if (cnt == 0)
			cnt++;
		cnt = BTN_DEBOUNCE_TIME_MS;
	} else if (cnt != 0)
		cnt--;
}

/* FIXME: fix delays */
static void
lcd_init(void)
{
	LCD_PORT_DATA = 0;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 0;
	TRISC = OUTPUT;
	TRISD = OUTPUT;
	
	lcd_cmd(LCD_DISPLAY_INIT);
	delay_ms(150);
	lcd_cmd(LCD_DISPLAY_INIT);
	delay_ms(150);

	lcd_cmd(LCD_MODE);
	lcd_cmd(LCD_CURS_INC);
	lcd_cmd(LCD_CURS_ZERO);
	lcd_cmd(LCD_CLEAR);
	lcd_cmd(LCD_CURS_OFF);
}

/* FIXME: fix delays */
static void
lcd_data(uint8_t c, uint8_t rs)
{
	LCD_RS = rs;
	LCD_RW = 0;
	LCD_EN = 1;
	LCD_PORT_DATA = c;
	delay_ms(500);
	LCD_EN = 0;
}

static void
lcd_puts(const char *str)
{
	while (*str != '\0')
		lcd_putc(*str++);
}

void
main(void)
{
	tmr0_init();
	tmr0_set_event(&led_blink, 1000); /* Blink every 1 sec */
	tmr0_set_event(&button_debounce, 1);
	lcd_init();
	lcd_cmd(LCD_CURS_ZERO);
	lcd_puts("19390133");

	BTN_TRIS = INPUT;
	LED_PORT = 1; /* LED on */
	LED_TRIS = OUTPUT;

	for (;;) {
	}
}
