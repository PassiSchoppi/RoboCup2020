#ifndef PID_H_
#define PID_H_

#include <Arduino.h>
#include "config.h"

float pid(uint8_t motorSpeed, uint8_t distanceF, uint8_t distanceB, bool leftSide);

#endif
