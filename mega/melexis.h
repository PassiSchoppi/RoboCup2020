#ifndef MELEXIS_H_
#define MELEXIS_H_

#include "i2cmaster.h"
#include <Arduino.h>

/*
 *
 *      ---------------------
 *      |                   |
 *      |  A2           A4  |
 *      |        /|\        |
 *      |       / | \       |
 *      |         |         |
 *      |         |         |
 *      |  A6           A0  |
 *      |                   |
 *      --------------------- 
 *        MELEXIS POSITIONS
 * 
 */



struct Melexis {
    uint8_t address;
    float value;
};
// extern Melexis melexis[2];


// extern uint8_t nextMelexis;

void melexisInit();

void melexisInterrupt();

float melexisVerify(uint8_t i);

float melexisTemperature(uint8_t address);

int melexisChangeAddress(uint8_t newAddress);


#endif
