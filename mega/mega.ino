#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"
#include "pid.h"

uint8_t sensorData[6];

void setup() {
  	motorInit();
	sensorInit();
	initMap();

	Serial.begin(9600);
}

void loop() {
	readSensor(&sensorData[0]);
	Serial.print(sensorData[0]);	
	Serial.print(", ");
	// Serial.print(sensorData[1]);
	// Serial.println(sensorData[2]);
	// Serial.println(sensorData[3]);
	// Serial.println(sensorData[4]);
	// Serial.println(sensorData[5]);
	Serial.println("---");
	// motorSetLeftSpeed(pid(75, sensorData[0], sensorData[1], true));
	// motorSetRightSpeed(pid(75, sensorData[2], sensorData[3], false));
}
