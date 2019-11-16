#include "sensor.h"

void sensorInit(){
	pinMode(INTERUPT_PIN, OUTPUT);
	pinMode(9, INPUT);
}

void readSensor(){
	digitalWrite(INTERUPT_PIN, HIGH);
 	digitalWrite(INTERUPT_PIN, LOW);
	Serial.print(digitalRead(9));
 	/* Serial.print("Serial1.available() : ");
 	Serial.println(Serial1.available());
 	while(Serial1.available()>0)
 	{
   		Serial.print("Serial1.read() : ");
   		Serial.println(Serial1.read());
 	}
 	Serial.println("Serial1.available()<=0 : True");*/
}
