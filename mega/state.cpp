#include <Arduino.h>
#include "state.h"

uint8_t nothing(){
	Serial.println("hey");
	return 0;
}

uint8_t changeState(){
	switch((int) 0) {
		case 0 :
			return nothing();
			break;
		case 1 :
			return 1;
			break;
	}
}
