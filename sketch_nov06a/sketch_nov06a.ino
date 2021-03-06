#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define HOUR_HAND_OFFSET 23										//Change this value, guess and check what value makes the hour hand correct
#define MINUTE_HAND_OFFSET 2										//Change this using guess and check as well.
/*
***********
*Functions*
***********
*/
inline int changeToPercent(int raw)								//maps a pot value (0-1023) to a PWM value (0-254)
{
	return (raw/255)*100;
}


/*
*********
*Globals*
*********
*/
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *hourMotor = AFMS.getMotor(1);			 	//SET THIS
Adafruit_DCMotor *minuteMotor = AFMS.getMotor(2);		 	//SET THIS
register unsigned int selector_pin;								//the pin that the directoin switch is set to. SET THIS
bool run_forward = true;
unsigned int pot_pin, pot_value;									//potentiometer pin and value. set the pin


void setup()
{
	AFMS.begin();
	pinMode(selector_pin, INPUT);
	pinMode(pot_pin, INPUT);
}


void loop()
{
	run_forward = digitalRead(selector_pin);					//check the state of the selector
	pot_value = analogRead(pot_pin);								//read the potentiometer
	hourMotor->setSpeed(changeToPercent(pot_value)/(HOUR_HAND_OFFSET));				//set the speed of the hour hand
	minuteMotor->setSpeed(changeToPercent(pot_value)/(MINUTE_HAND_OFFSET));			//set the speed of the minute hand
	if (run_forward)																					//If the switch is set
	{
	 hourMotor->run(FORWARD);										//set the hor hand in motion
	 minuteMotor->run(FORWARD);									//set the minute hand in motion
	}
	else
	{
	 hourMotor->run(BACKWARD);										//move it backwards
	 minuteMotor->run(BACKWARD);
	}
	delay(100);															//let the motors run for some amount of time
	hourMotor->run(RELEASE);										//then stop them
	delay(10);															//If you don't need to stop the hour and minute hands at different times, delete this line
	minuteMotor->run(RELEASE);					
	delay(890);															//this whole thing loops once per second.
}