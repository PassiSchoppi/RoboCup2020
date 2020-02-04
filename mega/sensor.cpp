#include "sensor.h"
#include "buffer.h"

void sensorInit(){
	Serial1.begin(9600);
	pinMode(INTERUPT_PIN_A, OUTPUT);

	Serial3.begin(9600);
	pinMode(INTERUPT_PIN_B, OUTPUT);

	Buffer<4> sensorBuffer;
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
			if(bufferVar>100){
				sensorData[i]=(8*sensorData[i]+bufferVar)/9;
			}else{
				sensorData[i]=(8*sensorData[i]+100)/9;
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
	while(Serial3.available()<6){
		// Serial.println(Serial3.available());
	}
	while(Serial3.available())
	{
		if(i==10){
			Serial3.read();
		}
		bufferVar = Serial3.read();
		// zusammen mit alpha gibt es nun 0..10 sensordaten --> 11 sensoren
		if(i<11){
			if(bufferVar>100){
		 		sensorData[i]=(8*sensorData[i]+bufferVar)/9;
			}else{
		 		sensorData[i]=(8*sensorData[i]+100)/9;
			}
			// sensorData[i]=bufferVar;
			++i;
		}
	}

	// 															TEMP SENSOR
	// sensorData[]
	
	
	//0   [LF,
	//1   LB,
	//2   RF,
	//3   RB,
	//4   ACC_X,
	//5   ACC_Z,
	//6   BL,
	//7   FL,
	//8   BR,
	//9   FC,
	//10  BL,
	//11  TEMP_L,
	//12  TEMP_R]
} 
