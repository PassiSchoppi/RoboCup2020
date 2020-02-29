#include <Arduino.h>
#include "state.h"
#include "motor.h"
#include "sensor.h"
#include "wall.h"
#include "led.h"
#include "config.h"
#include "stabilize.h"

int average;
uint8_t lastState=0;

uint8_t nothing(){
	return 0;
}

void stateChange(uint8_t *state, uint8_t *sensorData){
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

			// ## get direction to drive to ##
			if(!wallExists(RIGHT, &sensorData[0])){
				// rechts drehen dann gerade aus
				*state = 2;
				break;
			}
			if(!wallExists(FRONT, &sensorData[0])){
				// rechts drehen dann gerade aus
				*state = 3;
				break;
			}
			if(!wallExists(LEFT, &sensorData[0])){
				// links drehen dann gerade aus
				*state = 4;
				break;
			}
			// wenn rechts und forne und links eine wand ist aber hinten keine
			if(!wallExists(BACK, &sensorData[0])){
				// 2x links drehen dann gerade aus
				*state = 5;
				break;
			}

			// wenn überall Wände sind:::
			*state = 1;
			LEDSetColor(OFF);

			Serial.println("kein neuer status");
			
			break;
		case 2:
			// turn right
			LEDSetColor(GREEN);
			// motorSetRightSpeed(-BASESPEED);
			// motorSetLeftSpeed(BASESPEED);
			motorDriveTo(RIGHT, BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
				average = average + abs(motorStepsMade(i));
			}
			average = average/4;
			if( average > STEPFFORRIGHT )
			{
				motorResetAllSteps();
				motorBrake();
				stabilize();
				*state = 3;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				lastState = *state;
				*state = 6;
			}
			break;
		case 3:
			// drive staight
			LEDSetColor(BLUE);
			// motorSetRightSpeed(pid(70, sensorData[2], sensorData[3], false));
			// motorSetLeftSpeed(pid(70, sensorData[0], sensorData[1], true));
			// motorSetRightSpeed(BASESPEED);
			// motorSetLeftSpeed(BASESPEED);
			motorDriveTo(FRONT, BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
				average = average + motorStepsMade(i);
			}
			average = average/4;
			if( average>STEPSFORONE ){
				motorResetAllSteps();
				// stabilize und dann neue entscheidung
				*state = 8;
			}
			// wenn zu nah an einer Wand
			if( sensorData[7]>132 ){
				// kurz zurück und dann neu entscheiden
				motorBrake();
				*state = 9;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				lastState = *state;
				*state = 6;
			}
			break;
		case 4:
			// drive left
			LEDSetColor(RED);
			// motorSetRightSpeed(BASESPEED);
			// motorSetLeftSpeed(-BASESPEED);
			motorDriveTo(LEFT, BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
					average = average + abs(motorStepsMade(i));
			}
			average = average/4;
			if(average > STEPSFORLEFT)
			{
				motorResetAllSteps();
				stabilize();
				*state = 3;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				lastState = *state;
				*state = 6;
			}
			break;
		case 5:
			// drive left
			LEDSetColor(TURQUOISE);
			// motorSetRightSpeed(BASESPEED);
			// motorSetLeftSpeed(-BASESPEED);
			motorDriveTo(LEFT, BASESPEED);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
					average = average + abs(motorStepsMade(i));
			}
			average = average/4;
			if(average > STEPSFORLEFT)
			{
				motorResetAllSteps();
				stabilize();
				*state = 4;
			}
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				lastState = *state;
				*state = 6;
			}
			// if( sensorData[] )
			break;
		case 6:
			// temp victim
			motorBrake();
			// try for 5 seconds and blink
			LEDSetColor(RED);
			delay(1000);
			if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
				LEDSetColor(OFF);
				delay(1000);
				sensorRead(&sensorData[0]);
				if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
					LEDSetColor(RED);
					delay(1000);
					sensorRead(&sensorData[0]);
					if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
						LEDSetColor(OFF);
						delay(1000);
						sensorRead(&sensorData[0]);
						if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
							LEDSetColor(RED);
							delay(1000);
							sensorRead(&sensorData[0]);
							if( sensorData[11]>VICTIMTEMP || sensorData[12]>VICTIMTEMP ){
								//move the servo motor
								kitdropperSetTo(POSMIDD);
								delay(1000);
								kitdropperSetTo(POSRIGHT);
								delay(1000);
								kitdropperSetTo(POSMIDD);
							}
						}
					}
				}
			}
			*state = lastState;
			break;
		case 7:
			// black tile
			motorBrake();
			*state = 1;
			break;
		case 8:
			// stabilize und dann neu entscheiden
			LEDSetColor(PINK);
			motorBrake();
			stabilize();
			motorBrake();
			motorResetAllSteps();
			*state = 1;
			break;
		case 9:
			//kurz zurück fahren
			motorBrake();
			motorDriveTo(BACK, BASESPEED);
			while(motorStepsMade(0)<23){
				motorCheckForStepsMade(0);
			}
			motorResetAllSteps();
			motorBrake();
			// stabilize und dann neu entscheiden
			*state = 8;
			break;
	}
}
