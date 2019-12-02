#include "Arduino.h"
#include "config.h"
#include "motor.h"
#include "sensor.h"
#include "map.h"
#include "pid.h"

uint8_t sensorData[11];

void setup() {
  	motorInit();
	sensorInit();
	initMap();

	Serial.begin(9600);
}

void loop() {
	// delay(1000);
	readSensor(&sensorData[0]);
	// Serial.print(sensorData[0]);	
	Serial.print(", ");
	// Serial.print(sensorData[1]);
	Serial.print(", ");
	// Serial.print(sensorData[2]);
	Serial.print(", ");
	// Serial.print(sensorData[3]);
	Serial.print(", ");
	// Serial.print(sensorData[4]);
	Serial.print(", ");
	// Serial.print(sensorData[5]);
	Serial.print(", ");
	// \/ bei weit sehr sprunghaft bei nah ok
	// Serial.print(sensorData[6]);
	Serial.print(", ");
	// \/ bei weit sehr sprunghaft bei nah ok
	Serial.print(sensorData[7]);
	Serial.print(", ");
	// \/ geht
	// Serial.print(sensorData[8]);
	Serial.print(", ");
	// Serial.print(sensorData[9]);
	Serial.print(", ");
	// Serial.print(sensorData[10]);

	Serial.println("---");
	// motorSetLeftSpeed(pid(75, sensorData[0], sensorData[1], true));
	// motorSetRightSpeed(75);
	// motorSetRightSpeed(pid(75, sensorData[2], sensorData[3], true));
}
