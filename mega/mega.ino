#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"
#include "pid.h"
#include "state.h"

uint8_t sensorData[11];
uint8_t state = 1;

void setup() {
  	motorInit();
	sensorInit();
	initMap();

	Serial.begin(9600);
}

void loop() {
	readSensor(&sensorData[0]);
	changeState(&state, &sensorData[0]);
}
