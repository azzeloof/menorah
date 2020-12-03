#pragma once

#include "Arduino.h"
#include "leds.h"

#define NUM_MODES 4

extern uint8_t mode;

void setupButton();
int checkButton();
