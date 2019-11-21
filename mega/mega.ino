#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"

float sensorData[6];

void setup() {
  	motorInit();
	sensorInit();
	initMap();

	Serial.begin(9600);
}

void loop() {
	readSensor(&sensorData[0]);
	// Serial.println(sensorData[0]);
	// Serial.println(sensorData[1]);
	// Serial.println(sensorData[2]);
	Serial.println(sensorData[3]);
	// Serial.println(sensorData[4]);
	// Serial.println(sensorData[5]);
	Serial.println("---");
	// motorSetLeftSpeed(75);
	// motorSetRightSpeed(75);
}
