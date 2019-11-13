#include "Arduino.h"
#include "motor.h"

void setup() {
  // put your setup code here, to run once:
  motorInit();
}

void loop() {
  motorSetLeftSpeed(75);
  motorSetRightSpeed(75);
}
