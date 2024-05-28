#include <Encoder.h>

#define PIN_ENC_CHAN1 2
#define PIN_ENC_CHAN2 3
#define PIN_L293D_IN 4
#define PIN_L293D_OUT 5
#define PIN_ULTRASONIC_ECHO 6
#define PIN_ULTRASONIC_TRIGGER 7
#define PIN_DCMOTOR 9
#define PIN_PIR 10
#define PIN_LED 13
#define PIN_TEMP A0

static Encoder enc(PIN_ENC_CHAN1, PIN_ENC_CHAN2);

void
setup()
{
	pinMode(PIN_ENC_CHAN1, INPUT);
	pinMode(PIN_ENC_CHAN2, INPUT);
	pinMode(PIN_L293D_IN, OUTPUT);
	pinMode(PIN_L293D_OUT, OUTPUT);
	pinMode(PIN_DCMOTOR, OUTPUT);
	pinMode(PIN_PIR, INPUT);
	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_ULTRASONIC_ECHO, INPUT);
	pinMode(PIN_ULTRASONIC_TRIGGER, OUTPUT);
	Serial.begin(9600);
}

void
loop()
{
	if (measure_distance() <= 40)
		open_door();
	if (measure_temp() > 20)
		fan();
	if (digitalRead(PIN_PIR) == HIGH)
		digitalWrite(PIN_LED, HIGH);
	else
		digitalWrite(PIN_LED, LOW);

	delay(10);
}

int
measure_distance()
{
	long duration;
	int distance;

	digitalWrite(PIN_ULTRASONIC_TRIGGER, LOW);
	delayMicroseconds(2);
	digitalWrite(PIN_ULTRASONIC_TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_ULTRASONIC_TRIGGER, LOW);

	duration = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);
	distance = (float)duration * 0.344 / 20;

	Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println(" cm");

	delay(100);

	return (distance);
}

void
open_door()
{
	long pos;
	int rot;

	analogWrite(PIN_L293D_IN, 30);
	analogWrite(PIN_L293D_OUT, 0);
	pos = enc.read() / 10;
	rot = abs(pos) / 10;

	Serial.print("Encoder position: ");
	Serial.println(pos);
	Serial.print("Encoder rotation: ");
	Serial.println(rot);
}

float
measure_temp()
{
	float temp;
	int adc;

	adc = analogRead(PIN_TEMP);
	temp = (float)adc * (5000 / 1024.0);
	temp = (temp - 500) / 10;

	Serial.print("Temperatue: ");
	Serial.print(temp);
	Serial.println(" C");

	delay(100);

	return (temp);
}

void
fan()
{
	int v;

	for (v = 0; v <= 255; v += 5)
		analogWrite(PIN_DCMOTOR, v);
	for (v = 255; v >= 0; v -= 5)
		analogWrite(PIN_DCMOTOR, v);
}
