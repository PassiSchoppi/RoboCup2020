#include <Arduino.h>
#include "state.h"
#include "motor.h"
#include "pid.h"
#include "sensor.h"
#include "wall.h"
#include "led.h"
#include "config.h"

int average;
uint8_t lastState=0;

uint8_t nothing(){
	return 0;
}

void changeState(uint8_t *state, uint8_t *sensorData){
	switch(*state) {
		case 0:
			// the end
			motorBrake();
			*state = nothing();
			LEDSetColor(OFF);
			break;
		case 1:
			motorBrake();
			// Serial.println("new status");
			LEDSetColor(WHITE);
			
			// FIXME
			delay(1000);

			// ## get direction to drive to ##
			/*Serial.print(isWall(FRONT, &sensorData[0]));Serial.print(" ");
			Serial.print(isWall(LEFT, &sensorData[0])); Serial.print(" ");
			Serial.print(isWall(RIGHT, &sensorData[0]));Serial.print(" ");
			Serial.println(isWall(BACK, &sensorData[0])); Serial.print(" ")*/;
			// wenn gar keine Wand dann fahre nach vorne
			if(!isWall(FRONT, &sensorData[0]) && !isWall(RIGHT, &sensorData[0]) && !isWall(LEFT, &sensorData[0]) && !isWall(BACK, &sensorData[0])){
				*state = 3;
				break;
			}

			if(!isWall(RIGHT, &sensorData[0])){
				*state = 2;
				break;
			}

			if(!isWall(FRONT, &sensorData[0])){
				*state = 3;
				break;
			}

			if(!isWall(LEFT, &sensorData[0])){
				*state = 4;
				break;
			}

			if(!isWall(BACK, &sensorData[0])){
				*state = 5;
				break;
			}

			// wenn überall Wände sind:::
			*state = 1;
			LEDSetColor(OFF);

			Serial.println("kein neuer status");
			
			break;
		case 2:
			LEDSetColor(GREEN);
			motorSetRightSpeed(-BASESPEED);
			motorSetLeftSpeed(BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
				average = average + abs(stepsMotorMade(i));
			}
			average = average/4;
			if( average > STEPFFORTURN )
			{
				resetAllSteps();
				*state = 1;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				lastState = *state;
				*state = 6;
			}
			break;
		case 3:
			LEDSetColor(BLUE);
			// motorSetRightSpeed(pid(70, sensorData[2], sensorData[3], false));
			// motorSetLeftSpeed(pid(70, sensorData[0], sensorData[1], true));
			motorSetRightSpeed(BASESPEED);
			motorSetLeftSpeed(BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
				average = average + stepsMotorMade(i);
			}
			average = average/4;
			if( average>STEPSFORONE ){
				resetAllSteps();
				*state = 1;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				lastState = *state;
				*state = 6;
			}
			break;
		case 4:
			LEDSetColor(RED);
			motorSetRightSpeed(BASESPEED);
			motorSetLeftSpeed(-BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
					average = average + abs(stepsMotorMade(i));
			}
			average = average/4;
			if(average > STEPFFORTURN)
			{
				resetAllSteps();
				*state = 1;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				lastState = *state;
				*state = 6;
			}
			break;
		case 5:
			LEDSetColor(TURQUOISE);
			motorSetRightSpeed(BASESPEED);
			motorSetLeftSpeed(-BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
					average = average + abs(stepsMotorMade(i));
			}
			average = average/4;
			if(average > STEPFFORTURN)
			{
				resetAllSteps();
				*state = 1;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				lastState = *state;
				*state = 6;
			}
			break;
		case 6:
			motorBrake();
			LEDSetColor(RED);
			delay(1000);
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				delay(1000);
				if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
					delay(1000);
					if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
						delay(1000);
						if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
							delay(1000);
							if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
								//move the servo motor
							}
						}
					}
				}
			}
			*state = lastState;
			break;
	}
}
