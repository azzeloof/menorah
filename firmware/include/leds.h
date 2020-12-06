#pragma once

#include "Arduino.h"

#define NUM_NODES 12
#define NUM_LEDS 9

extern uint8_t Level[NUM_NODES];
extern uint8_t Order[NUM_LEDS];
extern uint8_t LogLevels[64];

void setupLeds();
void setLed(uint8_t led, uint8_t level);
void setLedLog(uint8_t led, uint8_t level);
void clearLeds();
void allOn();
