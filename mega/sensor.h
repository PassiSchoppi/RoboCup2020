#ifndef SENSOR_H_
#define SENSOR_H_

#include <Arduino.h>
#include "config.h"
#include "melexis.h"

void sensorInit();
void readSensor(uint8_t *sensorData);

#endif
