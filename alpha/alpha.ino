#include "Arduino.h"
#include "config.h"

void setup() {
	pinMode(INTERUPT_PIN, INPUT_PULLUP);
	Serial.begin(19200);
	attachInterrupt(digitalPinToInterrupt(INTERUPT_PIN), interupt, RISING);
}

void loop() {
	uint8_t sensorData[6];
	int calcVar;

/*
 *
 *           Sensordata in ARRAYINDEX
 *
 *             +-------------------+
 *             |                   |
 *      SHP_LF |  0   ACC_X 4   2  | SHP_RF
 *             |        /|\        |
 *             |         |         |
 *             |         |         |
 *             |         *         |
 *      SHP_LB |  1   ACC_Z 5   3  | SHP_RB
 *             |                   |
 *             +-------------------+ 
 *
 * 
 */

/*	sensorData[0] = analogRead(SHP_LF);
	sensorData[1] = analogRead(SHP_LB);
	sensorData[2] = analogRead(SHP_RF);
	sensorData[3] = analogRead(SHP_RB);
	sensorData[4] = analogRead(ACC_X);
	sensorData[5] = analogRead(ACC_Z);

	if(digitalRead(INTERUPT_PIN)){
	// if(true){
		for(uint8_t i=0; i<5; ++i){
			Serial.write(sensorData[i]);
		}
	}*/
}

void interupt(){
	uint8_t sensorData[6];

	sensorData[0] = analogRead(SHP_LF);
	sensorData[1] = analogRead(SHP_LB);
	sensorData[2] = analogRead(SHP_RF);
	sensorData[3] = analogRead(SHP_RB);
	sensorData[4] = analogRead(ACC_X);
	sensorData[5] = analogRead(ACC_Z);

	for(uint8_t i=0; i<6; ++i){
		Serial.write(sensorData[i]);
	}
}
