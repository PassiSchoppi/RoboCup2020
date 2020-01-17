#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include "config.h"

/*
 *
 *                 pin1/pin2:pwm
 *
 *             +---------------------+
 *             |                     |
 *     29/27:4 |  0 A           D 2  | 49/47:5
 *             |          /|\        |
 *             |         / | \       |
 *             |           |         |
 *             |           |         |
 *     23/25:3 |  1 B           C 3  | 51/53:6
 *             |                     |
 *             +---------------------+ 
 *                MOTOR POSITIONS
 * 
 */

struct Motor {
    uint8_t pin1;
    uint8_t pin2;
	uint8_t enc1;
	uint8_t enc2;
	short int 	steps;
	bool 	lastEncSignal;
    uint8_t pwm;
    double  factor;
};

void motorInit();

void motorSetSpeed(uint8_t motor, int16_t speed);

void checkForStepsMade(uint8_t i);

void resetAllSteps();

short int stepsMotorMade(uint8_t i);

void motorSetLeftSpeed(int16_t speed);

void motorSetRightSpeed(int16_t speed);

void motorBrake();


#endif
