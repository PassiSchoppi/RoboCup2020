#ifndef SENSOR_H_
#define SENSOR_H_

#include <Arduino.h>
#include "config.h"
#include "melexis.h"

void sensorInit();

// reads and saves all sensor data to sensorData
void sensorRead(uint8_t *sensorData);

bool dontTryMe();

#endif
