#include "sensor.h"

void sensorInit(){
	Serial1.begin(9600);
	pinMode(INTERUPT_PIN_A, OUTPUT);

	Serial3.begin(9600);
	pinMode(INTERUPT_PIN_B, OUTPUT);
}

void readSensor(uint8_t *sensorData){
	uint8_t i=0;
	uint8_t bufferVar=0;
	uint8_t newBufferVar;

	// 														ALPHA
	//wenn noch Daten da sind kein Interrupt
	if(!Serial1.available()){
		digitalWrite(INTERUPT_PIN_A, HIGH);
		digitalWrite(INTERUPT_PIN_A, LOW);
	}
	// warten auf Antwort (Programm könnte stecken bleiben)
	while(Serial1.available()<6){}
	while(Serial1.available())
 	{
		bufferVar = Serial1.read();
		// nur die ersten sechs weil alpha nur 0..5 sensoren schickt
		if(i<6){
			if(bufferVar>25){
				sensorData[i]=(8*sensorData[i]+bufferVar)/9;
			}else{
				sensorData[i]=(8*sensorData[i]+25)/9;
			}
			++i;
		}
	}


	// 														BETA
	// wenn noch daten da sind kein Interrupt
	if(!Serial3.available()){
		digitalWrite(INTERUPT_PIN_B, HIGH);
		digitalWrite(INTERUPT_PIN_B, LOW);
	}
	// auf Antwort warten (Programm könnte stecken bleiben)
	while(Serial3.available()<5){}
	while(Serial3.available())
	{
		bufferVar = Serial3.read();
		// zusammen mit alpha gibt es nun 0..10 sensordaten --> 11 sensoren
		if(i<11){
			if(bufferVar>25){
		 		sensorData[i]=(15*sensorData[i]+bufferVar)/16;
			}else{
		 		sensorData[i]=(15*sensorData[i]+25)/16;
			}
			++i;
		}
	}

	// Serial.println(i);

	// 															TEMP SENSOR
	// sensorData[]
	
	
	//0   [LF,
	//1   LB,
	//2   RF,
	//3   RB,
	//4   ACC_X,
	//5   ACC_Z,
	//6   FL,
	//7   FC,
	//8   FR, ???
	//9   BL,
	//10  BR,
	//11  TEMP_L,
	//12  TEMP_R]
} 
