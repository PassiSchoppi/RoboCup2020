#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"
#include "pid.h"
#include "state.h"
#include "led.h"

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
	Serial.println("anfange");
	digitalWrite(13, !digitalRead(13));

	// state = 1;
	readSensor(&sensorData[0]);
	for(uint8_t i=0; i<4; i++){
		checkForStepsMade(i);
	}
	// motorSetLeftSpeed(50);
	// motorSetRightSpeed(50);
    // Serial.println(stepsMotorMade(0));
	// Serial.println(stepsMotorMade(1));
	// Serial.println(stepsMotorMade(2));
	// Serial.println(stepsMotorMade(3));
	// Serial.println(sensorData[0]);
	// Serial.println(sensorData[1]);
	// Serial.println(sensorData[2]);
	// Serial.println(sensorData[3]);
	// Serial.println(sensorData[4]);
	// Serial.println(sensorData[5]);
	// Serial.println(state);
	// Serial.println(analogRead(3));
	
	changeState(&state, &sensorData[0]);
	Serial.println(state);
	Serial.println("ende");
}

