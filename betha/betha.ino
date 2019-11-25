#include "Arduino.h"
#include "config.h"

void setup() {
	pinMode(INTERUPT_PIN, INPUT_PULLUP);
	Serial.begin(38400);
	attachInterrupt(digitalPinToInterrupt(INTERUPT_PIN), interupt, RISING);
}

void loop() {
	uint8_t sensorData[5];
	int calcVar;


	//              EDIT THIS \/ \/ \/

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

	 // interupt();
	Serial.write(69);
}

void interupt(){
	uint8_t sensorData[6];

	sensorData[0] = analogRead(SHP_FL);
	sensorData[1] = analogRead(SHP_FC);
	sensorData[2] = analogRead(SHP_FR);
	sensorData[3] = analogRead(SHP_BL);
	sensorData[4] = analogRead(SHP_BR);

	for(uint8_t i=0; i<5; ++i){
		Serial.write(sensorData[i]);
	}
}
