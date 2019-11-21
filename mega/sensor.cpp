#include "sensor.h"

void sensorInit(){
	Serial1.begin(19200);
	pinMode(INTERUPT_PIN, OUTPUT);
}

void readSensor(float *sensorData){
	int i=0;
	float bufferVar;
	// set INTERUPT and wait for response
	digitalWrite(INTERUPT_PIN, HIGH);
	while(Serial1.available()==0){}
	digitalWrite(INTERUPT_PIN, LOW);
	delay(100);
	// save first six vars to sensorData
	while(Serial1.available())
 	{
		bufferVar = Serial1.read();
		if(i<6){
			sensorData[i]=round(bufferVar);
			++i;
		}
	}
 }
