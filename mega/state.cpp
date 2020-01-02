#include <Arduino.h>
#include "state.h"
#include "motor.h"
#include "pid.h"
#include "sensor.h"
#include "wall.h"
#include "led.h"
#include "config.h"

uint8_t nothing(){
	return 0;
}

void changeState(uint8_t *state, uint8_t *sensorData){
	switch(*state) {
		case 0:
			// the end
			*state = nothing();
			setLED(OFF);
			break;
		case 1:
			// get direction to drive to
			if(!isWall(RIGHT, &sensorData[0])){
				*state = 2;
				break;
			}else if(!isWall(FRONT, &sensorData[0])){
				*state = 3;
				break;
			}else if(!isWall(LEFT, &sensorData[0])){
				*state = 4;
				break;
			}else if(!isWall(BACK, &sensorData[0])){
				*state = 5;
				break;
			}else{
				*state = 0;
			}
			*state = 3;
			break;
		case 2:
			// turn right
			motorSetRightSpeed(-100);
			motorSetLeftSpeed(100);
			*state = 1;
			break;
		case 3:
			// drive straight
			motorSetRightSpeed(pid(100, sensorData[2], sensorData[3], false));
			motorSetLeftSpeed(pid(100, sensorData[0], sensorData[1], true));
			*state = 1;
			break;
		case 4:
			// turn left
			motorSetRightSpeed(100);
			motorSetLeftSpeed(-100);
			*state = 1;
			break;
		case 5:
			// full turn
			motorSetRightSpeed(100);
			motorSetLeftSpeed(-100);
			*state = 1;
			break;
	}
}
