const int PL_BUTTON = 2;
const int PL_LED_RED = 6;
const int PL_LED_GREEN = 7;
const int TL_LED_RED = 3;
const int TL_LED_ORANGE = 4;
const int TL_LED_GREEN = 5;

const int NSTATES = 4;

volatile int curstate = 0;

ISR(TIMER1_COMPA_vect)
{
	int btn_state;

	btn_state = digitalRead(PL_BUTTON);
	if (btn_state == HIGH) {
		delay(100);	/* lazy debounce */
		curstate = 1;
	}
}

void
timer_init()
{
	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 6249;
	TCCR1B |= (1 << WGM12) | (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	interrupts();
}

void
state0()
{
	digitalWrite(PL_LED_RED, HIGH);
	digitalWrite(PL_LED_GREEN, LOW);
	digitalWrite(TL_LED_RED, LOW);
	digitalWrite(TL_LED_ORANGE, LOW);
	digitalWrite(TL_LED_GREEN, HIGH);
	delay(4000);
}

void
state1()
{
	digitalWrite(PL_LED_RED, HIGH);
	digitalWrite(PL_LED_GREEN, LOW);
	digitalWrite(TL_LED_RED, LOW);
	digitalWrite(TL_LED_ORANGE, HIGH);
	digitalWrite(TL_LED_GREEN, LOW);
	delay(2000);
}

void
state2()
{
	digitalWrite(PL_LED_RED, LOW);
	digitalWrite(PL_LED_GREEN, HIGH);
	digitalWrite(TL_LED_RED, HIGH);
	digitalWrite(TL_LED_ORANGE, LOW);
	digitalWrite(TL_LED_GREEN, LOW);
	delay(4000);
}

void
state3()
{
	digitalWrite(PL_LED_RED, HIGH);
	digitalWrite(PL_LED_GREEN, LOW);
	digitalWrite(TL_LED_RED, HIGH);
	digitalWrite(TL_LED_ORANGE, LOW);
	digitalWrite(TL_LED_GREEN, LOW);
	delay(3000);
}

void
setup()
{
	pinMode(PL_BUTTON, INPUT);
	pinMode(PL_LED_RED, OUTPUT);
	pinMode(PL_LED_GREEN, OUTPUT);
	pinMode(TL_LED_RED, OUTPUT);
	pinMode(TL_LED_ORANGE, OUTPUT);
	pinMode(TL_LED_GREEN, OUTPUT);

	timer_init();
	Serial.begin(9600);
}

void (*states[NSTATES])() = {
	state0,
	state1,
	state2,
	state3,
};

void
loop()
{
	curstate %= NSTATES;
	(*states[curstate++])();
}
