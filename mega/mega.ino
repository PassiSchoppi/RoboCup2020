#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"
#include "pid.h"
#include "state.h"
#include "led.h"
#include "wall.h"
#include "i2cmaster.h"
#include "melexis.h"

uint8_t sensorData[15];
uint8_t state;

void setup() {
	state = 1;

	// ## INIT ##
  	motorInit();
	sensorInit();
	melexisInit();
	mapInit();
	
	Serial.begin(2000000);
}


void loop() {
	// ## LED ##
	digitalWrite(13, !digitalRead(13));
	
	// ## SENSORS ##
	readSensor(&sensorData[0]);

	// ## MOTOR ##
	for(uint8_t i=0; i<4; i++){
		checkForStepsMade(i);
	}

	// ## OUTPUT ##
    // # MOTOREN #
	/*Serial.print(stepsMotorMade(0));Serial.print(" ");
	 Serial.print(stepsMotorMade(1));Serial.print(" ");
	 Serial.print(stepsMotorMade(2));Serial.print(" ");
	 Serial.println(stepsMotorMade(3));*/
	// # SIDE SHARPS #
	/*Serial.print(sensorData[0]);Serial.print(" ");
	 Serial.print(sensorData[1]);Serial.print(" ");
	 Serial.print(sensorData[2]);Serial.print(" ");
	 Serial.print(sensorData[3]);Serial.print(" ");*/
	// # ACC #
	/*Serial.print(sensorData[4]);Serial.print(" ");
	 Serial.println(sensorData[5]);*/
	// # FRONT/BACK SHARPS #
	/*Serial.print(sensorData[6]);Serial.print(" ");
	 Serial.print(sensorData[7]);Serial.print(" ");
	 Serial.print(sensorData[8]);Serial.print(" ");
	 Serial.print(sensorData[9]);Serial.print(" ");
	 Serial.println(sensorData[10]);*/
	// # MELEXIS #
	// melexisChangeAddress(0xA0);
	 Serial.print(sensorData[11]);Serial.print(" ");
	 Serial.println(sensorData[12]);
	// # LIGHT #
	/*Serial.print(sensorData[13]);Serial.print(" ");
	 Serial.println(sensorData[14]);*/
	// # ISWALL #
	/*Serial.print(isWall(FRONT, &sensorData[0]));Serial.print(" ");
	 Serial.print(isWall(RIGHT, &sensorData[0]));Serial.print(" ");
	 Serial.print(isWall(LEFT, &sensorData[0]));Serial.print(" ");
	 Serial.println(isWall(BACK, &sensorData[0]));*/


	// ## STATE ##
	changeState(&state, &sensorData[0]);
	// Serial.println(state);
	
	//FIXME
	// delay(100000);
}

