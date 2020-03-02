#ifndef STATE_H_
#define STATE_H_

#include <Arduino.h>
#include "config.h"
#include "kitdropper.h"
#include "map.h"
#include "map.h"

uint8_t nothing();

// gets next step of state machine
void stateChange(uint8_t *state, uint8_t *sensorData, uint8_t *robot_is_facing, Vector *robot_is_at);

#endif
