#include "Arduino.h"
#include "config.h"

void setup() {
	pinMode(INTERUPT_PIN, OUTPUT);
}

void loop() {
	digitalWrite(INTERUPT_PIN, HIGH);
}
