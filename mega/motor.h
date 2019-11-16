#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include "config.h"

/*
 *
 *                 pin1/pin2:pwm
 *
 *             +-------------------+
 *             |                   |
 *     29/27:4 |  0             2  | 49/47:5
 *             |        /|\        |
 *             |       / | \       |
 *             |         |         |
 *             |         |         |
 *     23/25:3 |  1             3  | 51/53:6
 *             |                   |
 *             +-------------------+ 
 *                MOTOR POSITIONS
 * 
 */

struct Motor {
    uint8_t pin1;
    uint8_t pin2;
    uint8_t pwm;
    double factor;
};

void motorInit();

void motorSetSpeed(uint8_t motor, int16_t speed);

void motorSetLeftSpeed(int16_t speed);

void motorSetRightSpeed(int16_t speed);

void motorBrake();


#endif
