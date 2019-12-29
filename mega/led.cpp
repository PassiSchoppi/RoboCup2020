#include "led.h"
#include "config.h"

void setLED(uint8_t color){
	Serial3.write(color);
}
