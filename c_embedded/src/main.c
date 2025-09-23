#define NO_BIT_DEFINES
#include <pic14regs.h>
#include <stdint.h> 
/*#include <string.h>*/

static __code uint16_t __at (_CONFIG) __configword =
    _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _LVP_OFF & _WRT_OFF & _BOREN_ON &
    _CPD_OFF & _CP_OFF;

/* MCU related constants */
#define _XTAL_FREQ 16000000		/* Crystal oscillator running at 16MHz */
#define TMR0_CLK0 (0 << 5)		/* Use the CLK0 pin */
/*
 * Bit 3 assigns the prescalar to TMR0.
 * Bits 0-2 of OPTION_REG indicate the prescalar value. In this case,
 * 111 indicates a prescalar value of 256.
 */
#define TMR0_PRESCALAR_256 0b0111
/* 
 * We want 1ms delay @ 16Mhz with 64 prescalar, the formula is:
 *
 * 256 - ((delay * (fosc / 1000)) / (prescalar * 4)) =
 * 256 - ((1 * (16000000 / 1000)) / (256 * 4)) =
 * 256 - ((1 * 16000) / (256 * 4)) = ~240
 *
 * sdcc thinks there's an overflow here (hint: he's wrong)...
 */
#define TMR0_DELAY (256 - ((1 * (_XTAL_FREQ / 1000)) / (256 * 4)))
#define TMR0_REQ_MAX 3

#define BTN_PORT PORTBbits.RB0
#define BTN_TRIS TRISBbits.TRISB0
#define BTN_DEBOUNCE_TIME_MS 20

#define LED_PORT PORTBbits.RB1
#define LED_TRIS TRISBbits.TRISB1

#define LCD_RS PORTCbits.RC0	/* Instruction reg: 0, Data reg: 1 */
#define LCD_RW PORTCbits.RC1	/* Write: 0, Read: 1 */
#define LCD_EN PORTCbits.RC2	/* Enable read/write */
#define LCD_PORT_DATA PORTD
#define LCD_PORT_DATA_DIR TRISD
#define LCD_PORT_CTL_DIR TRISC
#define LCD_SEL_INST 0		/* Instruction register for RS */
#define LCD_SEL_DATA 1		/* Data register for RS */
#define LCD_CLEAR 0x01		/* Clear screen */
#define LCD_CURS_ROW1 0x02	/* Set cursor on (0, 0) */
#define LCD_CURS_ROW2 0xc0	/* Set cursor on (1, 0) */
#define LCD_CURS_INC 0x06	/* Auto-increment cursor */
#define LCD_CURS_OFF 0x0c	/* Hide cursor */
#define LCD_MODE 0x38		/* 8-bit, 16x2 */

#define OUTPUT 0
#define INPUT 1

/* Non MCU related constants */
#define NULL ((void *)0)
#define BUFSIZ (3 * sizeof(uint32_t))

/* Function macros */
#define lcd_putc(c) lcd_data(c, LCD_SEL_DATA)
#define lcd_cmd(cmd) lcd_data(cmd, LCD_SEL_INST)

typedef void (*ev_handler)(void);

struct timer_req {
	ev_handler handler;	/* ISR callback */
	uint32_t rate;		/* Interval */
	uint32_t cnt;		/* Current time */
};

/* Function declarations */
static void	tmr0_init(void);
static void	tmr0_delay_ms(uint32_t);
static int	tmr0_set_event(ev_handler, uint32_t);
static void	tmr0_isr(void) __interrupt;
static void	led_blink(void);
static void	button_debounce(void);
static void	lcd_init(void);
static void	lcd_data(uint8_t, uint8_t);
static void	lcd_puts(const char *);
static void	ctx_main(void);
static void	ctx_uptime_maxtp(void);
static char	*itoa(char *, uint32_t);
static void	*memset(void *, int, int);

/* Global variables */
static struct timer_req	reqs[TMR0_REQ_MAX];
static uint32_t	timecnt = 0;	/* Seconds passed since start */
static int	f_ctx = 0;	/* Change context */
static uint8_t	humid = 0;	/* Current humidity */
static int8_t	tp = 0;		/* Current temperature */
static int8_t	maxtp = 0;	/* Max temperature */
static char	buf[BUFSIZ+1] = {0}; /* Generic buffer */

/* Function implementations */
static void
tmr0_init(void)
{
	memset(reqs, 0, sizeof(reqs));
	OPTION_REG = 0;
	OPTION_REG |= TMR0_CLK0 | TMR0_PRESCALAR_256;
	TMR0 = TMR0_DELAY;
	INTCONbits.TMR0IE = 1;	/* TMR0 Interrupt Enable */
	INTCONbits.GIE = 1;	/* Global Interrupt Enable */
	INTCONbits.PEIE = 1;	/* Peripheral Interrupt Enable */
}

static void
tmr0_delay_ms(uint32_t t)
{
	while (t--) {
		while (INTCONbits.TMR0IF == 0)
			;	/* nothing */
		INTCONbits.TMR0IF = 0;
		TMR0 = TMR0_DELAY;
	}
}

static int
tmr0_set_event(ev_handler handler, uint32_t rate)
{
	struct timer_req *r;
	uint8_t i;

	for (i = 0; i < TMR0_REQ_MAX; i++) {
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
	for (i = 0; i < TMR0_REQ_MAX; i++) {
		r = &reqs[i];
		if (r->handler == NULL)
			continue;
		if (++r->cnt == r->rate) {
			r->handler();
			r->cnt = 0;
		}
	}
	TMR0 = TMR0_DELAY;
	INTCONbits.TMR0IF = 0; /* Clear interrupt flags */
}

static void
led_blink(void)
{
	LED_PORT ^= 1;
	/*
	 * Increment here since this function is called every 1 sec.
	 * No need to create another timer callback.
	 */
	timecnt++;
}

static void
button_debounce(void)
{
	static uint16_t cnt = 0;

	/* Button is pressed */
	if (BTN_PORT == 0) {
		if (cnt == 0) {
			/* Actual button functionality goes here. */
			f_ctx = 1;
			cnt++;
		}
		cnt = BTN_DEBOUNCE_TIME_MS;
	} else if (cnt != 0) {
		cnt--;
		f_ctx = 0;
	}
}

static void
lcd_init(void)
{
	LCD_PORT_CTL_DIR = OUTPUT;
	LCD_PORT_DATA_DIR = OUTPUT;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EN = 0;
	
	lcd_cmd(LCD_MODE);
	tmr0_delay_ms(15);
	lcd_cmd(LCD_CURS_ROW1);
	lcd_cmd(LCD_CURS_OFF);
	lcd_cmd(LCD_CURS_INC);
	lcd_cmd(LCD_CLEAR);
}

static void
lcd_data(uint8_t c, uint8_t rs)
{
	LCD_RS = rs;
	LCD_RW = 0;
	LCD_PORT_DATA = c;
	LCD_EN = 1;
	tmr0_delay_ms(2);
	LCD_EN = 0;
}

static void
lcd_puts(const char *str)
{
	while (*str != '\0')
		lcd_putc(*str++);
}

/* Helper to clean up the code below */
#define LCD_PUTS_BUF(buf, v) do {		\
	memset(buf, 0, sizeof(buf));		\
	lcd_puts(itoa(&buf[sizeof(buf)-1], v));	\
} while (0)

static void
ctx_main(void)
{
	lcd_cmd(LCD_CURS_ROW1);
	lcd_puts("19390133");

	lcd_cmd(LCD_CURS_ROW2);
	LCD_PUTS_BUF(buf, tp);
	lcd_puts("\337C    ");

	LCD_PUTS_BUF(buf, humid);
	lcd_puts("%");
}

static void
ctx_uptime_maxtp(void)
{
	lcd_cmd(LCD_CURS_ROW1);
	lcd_puts("T: ");
	LCD_PUTS_BUF(buf, timecnt);

	lcd_cmd(LCD_CURS_ROW2);
	lcd_puts("Max: ");
	LCD_PUTS_BUF(buf, maxtp);
	lcd_puts("\337C");
}

#undef LCD_PUTS_BUF

/*
 * To avoid reversing the string, the caller has to provide a pointer to the
 * end of the string.
 */
static char *
itoa(char *s, uint32_t n)
{
	*s = '\0';
	if (n == 0)
		*--s = '0';
	for (; n; n /= 10)
		*--s = n % 10 + '0';
	return (s);
}

static void *
memset(void *dst, int v, int len)
{
	uint8_t *dst0;

	dst0 = dst;
	while (len--)
		*dst0++ = v;
	return (dst);
}

void
main(void)
{
	tmr0_init();
	tmr0_set_event(&led_blink, 1000);
	tmr0_set_event(&button_debounce, 1);
	lcd_init();

	BTN_TRIS = INPUT;
	LED_PORT = 0; /* LED on */
	LED_TRIS = OUTPUT;

	for (;;) {
		lcd_cmd(LCD_CLEAR);
		if (!f_ctx)
			ctx_main();
		else
			ctx_uptime_maxtp();
		tmr0_delay_ms(1000);
	}
}
