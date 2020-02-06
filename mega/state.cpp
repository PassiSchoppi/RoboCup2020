#include <Arduino.h>
#include "state.h"
#include "motor.h"
#include "pid.h"
#include "sensor.h"
#include "wall.h"
#include "led.h"
#include "config.h"

int average;

uint8_t nothing(){
	return 0;
}

void changeState(uint8_t *state, uint8_t *sensorData){
	switch(*state) {
		case 0:
			// the end
			motorBrake();
			*state = nothing();
			setLED(OFF);
			break;
		case 1:
			motorBrake();
			// Serial.println("new status");
			setLED(WHITE);

			//FIXME
			delay(1000);
			// ## get direction to drive to ##
			/*Serial.print(isWall(FRONT, &sensorData[0]));Serial.print(" ");
			Serial.print(isWall(LEFT, &sensorData[0])); Serial.print(" ");
			Serial.print(isWall(RIGHT, &sensorData[0]));Serial.print(" ");
			Serial.println(isWall(BACK, &sensorData[0])); Serial.print(" ")*/;
			// wenn gar keine Wand dann fahre nach vorne
			if(!isWall(FRONT, &sensorData[0]) && !isWall(RIGHT, &sensorData[0]) && !isWall(LEFT, &sensorData[0]) && !isWall(BACK, &sensorData[0])){
				*state = 3;
				setLED(BLUE);
				break;
			}

			if(!isWall(RIGHT, &sensorData[0])){
				*state = 2;
				setLED(GREEN);
				break;
			}

			if(!isWall(FRONT, &sensorData[0])){
				*state = 3;
				setLED(BLUE);
				break;
			}

			if(!isWall(LEFT, &sensorData[0])){
				*state = 4;
				setLED(RED);
				break;
			}

			if(!isWall(BACK, &sensorData[0])){
				*state = 5;
				setLED(TURQUOISE);
				break;
			}

			// wenn überall Wände sind:::
			*state = 1;
			setLED(OFF);

			Serial.println("kein neuer status");
			
			break;
		case 2:
			motorSetRightSpeed(-110);
			motorSetLeftSpeed(100);
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
			break;
		case 3:
			// motorSetRightSpeed(pid(70, sensorData[2], sensorData[3], false));
			// motorSetLeftSpeed(pid(70, sensorData[0], sensorData[1], true));
			motorSetRightSpeed(100);
			motorSetLeftSpeed(100);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
				average = average + stepsMotorMade(i);
			}
			average = average/4;
			// Serial.println(average);
			if( average>STEPSFORONE ){
				resetAllSteps();
				*state = 1;
			}
			break;
		case 4:
			motorSetRightSpeed(100);
			motorSetLeftSpeed(-110);
			average = 0;
			for(uint8_t i=0; i<4; ++i){
					average = average + abs(stepsMotorMade(i));
			}
			average = average/4;
			// Serial.println(average);
			if(average > STEPFFORTURN)
			{
				resetAllSteps();
				*state = 1;
			}
			break;
		case 5:
			motorSetRightSpeed(70);
			motorSetLeftSpeed(-80);
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
			break;
	}
}
