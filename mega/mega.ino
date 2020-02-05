#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"
#include "pid.h"
#include "state.h"
#include "led.h"
#include "buffer.h"
#include "wall.h"

uint8_t sensorData[11];
uint8_t state;

bool lastTimeEncState;

void setup() {
	state = 1;
  	motorInit();
	sensorInit();
	initMap();
	Serial.begin(9600);
	pinMode(A3, INPUT);
}

void loop() {
	// ## LED ##
	// Serial.println("anfang");
	digitalWrite(13, !digitalRead(13));
	
	// ## SENSORS ##
	readSensor(&sensorData[0]);
	
	// ## MOTOR ##
	for(uint8_t i=0; i<4; i++){
	 	checkForStepsMade(i);
	}
	
	// ## OUTPUT ##
	// motorSetLeftSpeed(50);
	// motorSetRightSpeed(50);
    // Serial.println(stepsMotorMade(0));
	// Serial.println(stepsMotorMade(1));
	// Serial.println(stepsMotorMade(2));
	Serial.println(stepsMotorMade(3));
	// # SIDE SHARPS #
	// Serial.println(sensorData[0]);
	// Serial.println(sensorData[1]);
	// Serial.println(sensorData[2]);
	// Serial.println(sensorData[3]);
	// # TEMP #
	// Serial.println(sensorData[4]);
	// Serial.println(sensorData[5]);
	// # FRONT/BACK SHARPS #
	// Serial.write("6:  ");Serial.println(sensorData[6]);
	// Serial.write("7:  ");Serial.println(sensorData[7]);
	// Serial.write("8:  ");Serial.println(sensorData[8]);
	// Serial.write("9:  ");Serial.println(sensorData[9]);
	// Serial.write("10: ");Serial.println(sensorData[10]);
	// Serial.println(state);
	// Serial.println(analogRead(3));
	// Serial.println(isWall(RIGHT, &sensorData[0]));
	changeState(&state, &sensorData[0]);
	// Serial.println(state);
	// Serial.println("ende");

	//FIXME
	// delay(100000);
}

