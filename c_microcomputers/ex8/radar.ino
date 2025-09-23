#include <LiquidCrystal.h>
#include <Servo.h>

#define PIN_SERVO_X 3
#define PIN_SERVO_Y 4
#define PIN_ULTRASONIC_ECHO 11
#define PIN_ULTRASONIC_TRIGGER 12

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);
Servo servo_x, servo_y;

void
setup()
{
	pinMode(PIN_ULTRASONIC_ECHO, INPUT);
	pinMode(PIN_ULTRASONIC_TRIGGER, OUTPUT);
	servo_x.attach(PIN_SERVO_X);
	servo_y.attach(PIN_SERVO_Y);
	servo_x.write(0);
	servo_y.write(0);
	lcd.begin(16, 2);
	Serial.begin(9600);
}

void
loop()
{
	int x, y;

	/*
	 * in reality, the ultrasonic sensor is supposed to be mounted on the 2
	 * servos so that it is able to move around.
	 */
	for (x = 0; x < 180; x++)
		for (y = 0; y < 180; y++)
			move_and_calc_distance(x, y);
	for (x = 180; x >= 0; x--)
		for (y = 180; y >= 0; y--)
			move_and_calc_distance(x, y);
	
	delay(250);
}

void
move_and_calc_distance(int x, int y)
{
	float pingtime, distance;

	servo_x.write(x);
	servo_y.write(y);
	delay(10);

	digitalWrite(PIN_ULTRASONIC_TRIGGER, LOW);
	delayMicroseconds(2);
	digitalWrite(PIN_ULTRASONIC_TRIGGER, HIGH);
	delayMicroseconds(10);
	digitalWrite(PIN_ULTRASONIC_TRIGGER, LOW);

	pingtime = pulseIn(PIN_ULTRASONIC_ECHO, HIGH);
	/* calculate distance in cm */
	distance = (float)pingtime * 0.344 / 20;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Distance: ");
	lcd.setCursor(0, 1);
	lcd.print(distance);
	lcd.print(" cm");
	delay(50);
}
