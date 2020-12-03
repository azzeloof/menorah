#pragma once

#include "Arduino.h"

#define NUM_LEDS 12

extern uint8_t Level[NUM_LEDS];
extern uint8_t Order[NUM_LEDS];

void setupLeds();
void setLed(uint8_t led, uint8_t level);
void setLedLog(uint8_t led, uint8_t level);
void clearLeds();
void allOn();
