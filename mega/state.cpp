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
			Serial.println("new status");
			// get direction to drive to
			if(!isWall(RIGHT, &sensorData[0])){
				Serial.println("drehe rechts");
				*state = 2;
				motorSetRightSpeed(-50);
				motorSetLeftSpeed(50);
				setLED(GREEN);
				break;
			}else if(!isWall(FRONT, &sensorData[0])){
				Serial.println("fahre nach vorn");
				*state = 3;
				motorSetRightSpeed(100);
				motorSetLeftSpeed(100);
				setLED(BLUE);
				break;
			}else if(!isWall(LEFT, &sensorData[0])){
				Serial.println("drehe links1");
				*state = 4;
				motorSetRightSpeed(100);
				motorSetLeftSpeed(-100);
				setLED(RED);
				break;
			}else if(!isWall(BACK, &sensorData[0])){
				Serial.println("drehe links2");
				*state = 5;
				motorSetRightSpeed(100);
				motorSetLeftSpeed(-100);
				setLED(YELLOW);
				break;
			}else{
				*state = 1;
			}
			// *state = 2;
			Serial.println("kein neuer status");
			break;
		case 2:
			// if(stepsMotorMade(0)>90 && stepsMotorMade(1)>90 && stepsMotorMade(2)<-90 && stepsMotorMade(3)<-90){
			// if(true){
			if(stepsMotorMade(0)>90){
				resetAllSteps();
				*state = 1;
			}
			break;
		case 3:
			// if(stepsMotorMade(0)>90 && stepsMotorMade(1)>90 && stepsMotorMade(2)>90 && stepsMotorMade(3)>90){
			if(true){
			// if(stepsMotorMade(0)>90){
				resetAllSteps();
				*state = 1;
			}
			break;
		case 4:
			// if(stepsMotorMade(0)<-90 && stepsMotorMade(1)<-90 && stepsMotorMade(2)>90 && stepsMotorMade(3)>90){
			if(true){
			// if(stepsMotorMade(2)>90){
				resetAllSteps();
				*state = 1;
			}
			break;
		case 5:
			// if(stepsMotorMade(0)<-90 && stepsMotorMade(1)<-90 && stepsMotorMade(2)>90 && stepsMotorMade(3)>90){
			if(true){
			// if(stepsMotorMade(2)>90){
				resetAllSteps();
				*state = 1;
			}
			break;
	}
}
