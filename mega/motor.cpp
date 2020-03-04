#include "motor.h"
#include <Arduino.h>
#include "sensor.h"

Motor motor[4];

uint8_t localSensorData[15];

void motorInit() 
{
  	motor[0].pin1 = 29;
  	motor[0].pin2 = 27;
  	motor[0].enc = &PINC;
	motor[0].encbit = 4;
	// motor[0].enc2 = PINC;
	// motor[0].enc2bit = 6;
	motor[0].steps = 1;
	motor[0].pwm = 4;
  	motor[0].factor = 0.9968225247;

  	motor[1].pin1 = 23;
  	motor[1].pin2 = 25;
	motor[1].enc = &PINC;
	motor[1].encbit = 0;
	// motor[1].enc2 = PINC;
	// motor[1].enc2bit = 2;
	motor[1].steps = 1;
  	motor[1].pwm = 3;
  	motor[1].factor = 0.9708457497;

  	motor[2].pin1 = 49;
  	motor[2].pin2 = 47;
	motor[2].enc = &PINL;
	motor[2].encbit = 4;
	// motor[2].enc2 = PINL;
	// motor[2].enc2bit = 2;
	motor[2].steps = 1;
  	motor[2].pwm = 5;
  	motor[2].factor = 0.9565686154;

  	motor[3].pin1 = 51;
  	motor[3].pin2 = 53;
	motor[3].enc = &PING;
	motor[3].encbit = 0;
	// motor[3].enc2 = PING;
	// motor[3].enc2bit = 2;
	motor[3].steps = 1;
  	motor[3].pwm = 6;
  	motor[3].factor = 1.00000000;

  	for(uint8_t i=0; i<4; i++) 
	{
    	pinMode(motor[i].pin1, OUTPUT);
    	pinMode(motor[i].pin2, OUTPUT);
    	// pinMode(motor[i].enc, INPUT);
		// pinMode(motor[i].enc2, INPUT);
		pinMode(motor[i].pwm, OUTPUT);
  	}
}

void motorSetSpeed(uint8_t i, int speed) 
{
  	int pwm = min(255, round(abs(speed)*motor[i].factor));

  	analogWrite(motor[i].pwm, pwm);
  	digitalWrite(motor[i].pin1, speed>=0);
  	digitalWrite(motor[i].pin2, speed<=0);
}

void motorCheckForStepsMade(uint8_t i)
{
	// momentanes siganal auf enc1 des Motors i
	bool currentEncSignal;
	currentEncSignal = (*motor[i].enc >> motor[i].encbit & 1);

	// wenn ein rising edge auf current state ist
	if(motor[i].lastEncSignal != currentEncSignal && currentEncSignal == HIGH)
	{
			motor[i].steps = (motor[i].steps + 1);
	}
	// update lastEncSignal
	motor[i].lastEncSignal = currentEncSignal;
}

void motorResetAllSteps()
{
	for(uint8_t i=0; i<4; i++)
	{
		motor[i].steps = 1;
	}
}

short int motorStepsMade(uint8_t i)
{
	return(motor[i].steps);
}

int speedFromEnc(uint8_t encA, uint8_t encB, uint8_t encC, uint8_t encME, int speedME, bool stickToWall, bool leftMotor)
{
	volatile uint8_t localSensorData[15];
	sensorRead(&localSensorData[0]);
	int correctedSpeed = ( ((encA+encB+encC+encME)/4) *speedME) / (encME);
	// Serial.println( localSensorData[2] );
	// Serial.println( wallExists(RIGHT, &localSensorData[0]) );
	if( stickToWall )
	{
		if( leftMotor )
		{
			if(wallExists(LEFT, &localSensorData[0]))
			{
				correctedSpeed = ((correctedSpeed * (localSensorData[0] + 0))/(localSensorData[1] + 0));
				Serial.println("correcting LEFT");
			}
		}
		else
		{
			if(wallExists(RIGHT, &localSensorData[0]))
			{
				correctedSpeed = ((correctedSpeed * (localSensorData[2] + 0))/(localSensorData[3] + 0));
				Serial.println("correcting RIGHT");
			}
		}
	}
	return (correctedSpeed);

	// return(speedME);
}

void motorDriveTo(uint8_t direction, int speed)
{
	switch( direction )
	{
		case FRONT:
			motorSetSpeed(0, speedFromEnc(motor[1].steps, motor[2].steps, motor[3].steps, motor[0].steps, speed, true, true));
			motorSetSpeed(1, speedFromEnc(motor[0].steps, motor[2].steps, motor[3].steps, motor[1].steps, speed, true, true));
			motorSetSpeed(2, speedFromEnc(motor[0].steps, motor[1].steps, motor[3].steps, motor[2].steps, speed, true, false));
			motorSetSpeed(3, speedFromEnc(motor[0].steps, motor[2].steps, motor[1].steps, motor[3].steps, speed, true, false));
			break;
		
		case RIGHT:
			motorSetSpeed(0, speedFromEnc(motor[1].steps, motor[2].steps, motor[3].steps, motor[0].steps, speed, false, true));
			motorSetSpeed(1, speedFromEnc(motor[0].steps, motor[2].steps, motor[3].steps, motor[1].steps, speed, false, true));
			motorSetSpeed(2, speedFromEnc(motor[0].steps, motor[1].steps, motor[3].steps, motor[2].steps, -speed, false, false));
			motorSetSpeed(3, speedFromEnc(motor[0].steps, motor[2].steps, motor[1].steps, motor[3].steps, -speed, false, false));
			break;
		
		case LEFT:
			motorSetSpeed(0, speedFromEnc(motor[1].steps, motor[2].steps, motor[3].steps, motor[0].steps, -speed, false, true));
			motorSetSpeed(1, speedFromEnc(motor[0].steps, motor[2].steps, motor[3].steps, motor[1].steps, -speed, false, true));
			motorSetSpeed(2, speedFromEnc(motor[0].steps, motor[1].steps, motor[3].steps, motor[2].steps, speed, false, false));
			motorSetSpeed(3, speedFromEnc(motor[0].steps, motor[2].steps, motor[1].steps, motor[3].steps, speed, false, false));
			break;
		
		case BACK:
			// FIXME
			motorSetSpeed(0, speedFromEnc(motor[1].steps, motor[2].steps, motor[3].steps, motor[0].steps, -speed, false, true));
			motorSetSpeed(1, speedFromEnc(motor[0].steps, motor[2].steps, motor[3].steps, motor[1].steps, -speed, false, true));
			motorSetSpeed(2, speedFromEnc(motor[0].steps, motor[1].steps, motor[3].steps, motor[2].steps, -speed, false, false));
			motorSetSpeed(3, speedFromEnc(motor[0].steps, motor[2].steps, motor[1].steps, motor[3].steps, -speed, false, false));
			break;
	}
}

void motorBrake() 
{
  	for(uint8_t i=0; i<4; i++) 
	{
    	motorSetSpeed(i, 0);
  	}
}
