#ifndef STATE_H_
#define STATE_H_

#include <Arduino.h>
#include "config.h"

uint8_t nothing();

// gets next step of state machine
void stateChange(uint8_t *state, uint8_t *sensorData);

#endif
