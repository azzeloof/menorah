/*
 * Snowflake Christmas Ornament
 * 
 * Sara Adkins & Adam Zeloof - December 2019
 * 
 * PWM code adapted from David Johnson-Davies - www.technoblogy.com - 19th February 2017
 * http://www.technoblogy.com/show?2H0K
 */

#include "Arduino.h"
#include "modeButton.h"
#include "leds.h"
#include "ringFade.h"
#include "twinkle.h"
#include "chaos.h"

// Timer/Counter1 overflow interrupt
ISR(TIM1_COMPA_vect) {
  static uint8_t row, ramp, column, bits, colbit;
  ramp = (ramp+1) & 0x3F;             // Count from 0 to 63
  if (ramp == 0) {
    bits = 0x07; //0000111                    // All on
    column = (column + 1) & 0x03; // Count from 0 to 3
    row = column * 3;               //0 3 6 9
    colbit = 1<<(column+0); // 0b0001 0b0010 0b0100 0b1000
  }

  //check if check col has reached its ramp
  if (Level[row] == ramp) bits = bits & 0x06; // 00000110, mask out pos 0
  if (Level[row+1] == ramp) bits = bits & 0x05; // 00000101, mask out pos 1
  if (Level[row+2] == ramp) bits = bits & 0x03; // 00000011, mask out pos 2
  
  uint8_t mask = colbit - 1; 
  
  uint8_t outputs = (bits & mask) | (bits & ~mask)<<1;
  DDRB = (outputs | colbit) << 1;
  PORTB = (outputs) << 1;
}

void setup() {
  // Set up Timer/Counter1 to multiplex the LEDs
  TCCR1 = 1<<CTC1 | 2<<CS10;          // Divide by 2
  GTCCR = 0;                          // No PWM
  OCR1A = 0;
  OCR1C = 250-1;                      // 16kHz
  TIMSK = TIMSK | 1<<OCIE1A;          // Compare Match A interrupt

  setupButton();
  setupLeds();
}

void allOnProgram()
{
  allOn();
  checkButton();
}

void allOffProgram()
{
  clearLeds();
  checkButton();
}

void loop () {
  switch(mode) {
    case 0:
      fadeProgram();
      break;
    case 1:
      twinkleProgram(20, 200);
      break;
    case 2:
      allOnProgram();
      break;   
    case 3:
      chaosProgram(80,20);
      break; 
    default:
      allOffProgram();
      break;
  }
}