#include <Servo.h>

/* photo resistor values tested and found on tinkercad */
#define LIGHT_NONE	640
#define LIGHT_FULL	33
#define SEVENTY_PERC	(180 * (70 / (float)100))

Servo servo;

void
setup()
{
	servo.attach(9);
	Serial.begin(9600);
}

void
loop()
{
	int pr_out, pr_in, pos = 0;

	pr_out = analogRead(A0);	/* exterior photoresistor */
	pr_in = analogRead(A1);		/* interior photoresistor */

	if (pr_out == LIGHT_NONE) {
		pos = 0;
		servo_write_and_delay(pos);
		Serial.println("night");
	} else if (pr_out < pr_in) {
		pos = map(pr_out, LIGHT_NONE, LIGHT_FULL, 0, 180);
		servo_write_and_delay(pos);
		Serial.println("day");
	} else {
		pos = SEVENTY_PERC;
		servo_write_and_delay(pos);
		Serial.println("peak");
	}
	Serial.println(pos);
}

void
servo_write_and_delay(int pos)
{
	servo.write(pos);
	delay(15);
}
