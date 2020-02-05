#include "motor.h"

Motor motor[4];

void motorInit() {
  	motor[0].pin1 = 29;
  	motor[0].pin2 = 27;
  	motor[0].enc1 = 31;
	motor[0].enc2 = 33;
	motor[0].steps = 0;
	motor[0].pwm = 4;
  	motor[0].factor = 0.9968225247;
	motor[0].direction = 0;

  	motor[1].pin1 = 23;
  	motor[1].pin2 = 25;
	motor[1].enc1 = 37;
	motor[1].enc2 = 35;
	motor[1].steps = 0;
  	motor[1].pwm = 3;
  	motor[1].factor = 0.9708457497;
	motor[1].direction = 0;

  	motor[2].pin1 = 49;
  	motor[2].pin2 = 47;
	motor[2].enc1 = 43;
	motor[2].enc2 = 45;
	motor[2].steps = 0;
  	motor[2].pwm = 5;
  	motor[2].factor = 0.9565686154;
	motor[2].direction = 0;

  	motor[3].pin1 = 51;
  	motor[3].pin2 = 53;
	motor[3].enc1 = 41;
	motor[3].enc2 = 39;
	motor[3].steps = 0;
  	motor[3].pwm = 6;
  	motor[3].factor = 1.00000000;
	motor[3].direction = 0;

  	for(uint8_t i=0; i<4; i++) {
    	pinMode(motor[i].pin1, OUTPUT);
    	pinMode(motor[i].pin2, OUTPUT);
    	pinMode(motor[i].enc1, INPUT);
		pinMode(motor[i].enc2, INPUT);
		pinMode(motor[i].pwm, OUTPUT);
  	}
}

void motorSetSpeed(uint8_t i, int16_t speed) {
  	uint8_t pwm = min(255, round(abs(speed)*motor[i].factor));

  	analogWrite(motor[i].pwm, pwm);
  	digitalWrite(motor[i].pin1, speed>=0);
  	digitalWrite(motor[i].pin2, speed<=0);
	motor[i].direction = speed;
}

void checkForStepsMade(uint8_t i){
	// wenn ein rising edge auf enc1 ist
	if(motor[i].lastEncSignal < digitalRead(motor[i].enc1)){
		// wenn da enc2 schon auf 1 ist
		if(digitalRead(motor[i].enc2)){
			// ist er nach forne gefahren
			motor[i].steps = (motor[i].steps + 1);
		}else{
			// oder er ist nach hinten gefahren
			motor[i].steps = (motor[i].steps - 1);
		}
	}
	// update lastEncSignal für enc1
	motor[i].lastEncSignal = digitalRead(motor[i].enc1);
}

void resetAllSteps(){
	for(uint8_t i=0; i<4; i++){
		motor[i].steps = 0;
	}
}

short int stepsMotorMade(uint8_t i){
	return(motor[i].steps);
}

void motorSetLeftSpeed(int16_t speed) {
  	motorSetSpeed(0, speed);
  	motorSetSpeed(1, speed);
}

void motorSetRightSpeed(int16_t speed) {
  	motorSetSpeed(2, speed);
  	motorSetSpeed(3, speed);
}

void motorBrake() {
  	for(uint8_t i=0; i<4; i++) {
    	motorSetSpeed(i, 0);
  	}
}
