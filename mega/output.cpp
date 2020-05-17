#include <Arduino.h>
#include "output.h"
#include "motor.h"
#include "sensor.h"
#include "config.h"

uint8_t myLocalSensorData[15];

void output()
{
	sensorRead(&myLocalSensorData[0]);
	Serial.println("########################################");
    // # MOTOREN #
	Serial.println("Motor Steps: 	");
	Serial.print(" 	Vorne Links: 	");Serial.println(motorStepsMade(0));
	Serial.print(" 	Hinten Links: 	");Serial.println(motorStepsMade(1));
	Serial.print(" 	Vorne Rechts: 	");Serial.println(motorStepsMade(2));
	Serial.print(" 	Hinten Rechts: 	");Serial.println(motorStepsMade(3));
	// # SIDE SHARPS #
	Serial.println("Sharps: 		");
	Serial.print(" 	Links Vorne: 	");Serial.println(myLocalSensorData[0]);
	Serial.print(" 	Links Hinten: 	");Serial.println(myLocalSensorData[1]);
	Serial.print(" 	Rechts Vorne: 	");Serial.println(myLocalSensorData[2]);
	Serial.print(" 	Rechts Hinten: 	");Serial.println(myLocalSensorData[3]);
	Serial.print(" 	Front Left: 	");Serial.println(myLocalSensorData[6]);
	Serial.print(" 	Front Center: 	");Serial.println(myLocalSensorData[7]);
	Serial.print(" 	Front Right: 	");Serial.println(myLocalSensorData[8]);
	Serial.print(" 	Back Left: 	");Serial.println(myLocalSensorData[9]);
	Serial.print(" 	Back Right: 	");Serial.println(myLocalSensorData[10]);
	// # ACC #
	Serial.println("Accelerometer: 	");
	Serial.print(" 	Y: 		");Serial.println(myLocalSensorData[4]);
	Serial.print(" 	Z: 		");Serial.println(myLocalSensorData[5]);
	// # MELEXIS #
	Serial.println("Melexis: 		");
	Serial.print(" 	Left: 		");Serial.println(myLocalSensorData[11]);
	Serial.print(" 	Right: 		");Serial.println(myLocalSensorData[12]);
	// # LIGHT #
	Serial.println("Light: 			");
	Serial.print(" 	Right: 		");Serial.println(myLocalSensorData[13]);
	Serial.print(" 	Left: 		");Serial.println(myLocalSensorData[14]);
	// # ISWALL #
	Serial.println("Walls: ");
	Serial.print(" 	FRONT: 		");Serial.println(wallExists(FRONT, &myLocalSensorData[0]));
	Serial.print(" 	RIGHT: 		");Serial.println(wallExists(RIGHT, &myLocalSensorData[0]));
	Serial.print(" 	LEFT: 		");Serial.println(wallExists(LEFT, &myLocalSensorData[0]));
	Serial.print(" 	BACK: 		");Serial.println(wallExists(BACK, &myLocalSensorData[0]));
}
