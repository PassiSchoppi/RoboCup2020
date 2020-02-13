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
	volatile uint8_t* enc;
	uint8_t encbit;
	// volatile uint8_t* enc2;
	// uint8_t enc2bit;
	short int 	steps;
	bool 	lastEncSignal;
    uint8_t pwm;
    double  factor;
	int16_t direction;
};

void motorInit();

void motorSetSpeed(uint8_t motor, int16_t speed);

void checkForStepsMade(uint8_t i);

void resetAllSteps();

short int stepsMotorMade(uint8_t i);

// void motorSetLeftSpeed(int16_t speed);

// void motorSetRightSpeed(int16_t speed);

int speedFromEnc(uint8_t encA, uint8_t encB, uint8_t encC, uint8_t encME, int speedME);

void motorDriveTo(uint8_t direction, int speed);

void motorBrake();


#endif
