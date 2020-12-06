/*
 * PCB Menorah
 * 
 * Adam Zeloof and Sara Adkins - December 2020
 * 
 * PWM code adapted from David Johnson-Davies - www.technoblogy.com - 19th February 2017
 * http://www.technoblogy.com/show?2H0K
 */

#include "Arduino.h"
#include "modeButton.h"
#include "leds.h"

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

uint8_t baseBrightness = 50;
uint8_t maxBrightness = 63;
uint8_t candleLevels[NUM_LEDS];
uint8_t candleFadeCounter[NUM_LEDS];
uint8_t candleFadeInit = 0; //32
uint8_t variability = 3;
uint8_t day = 0;
uint8_t flickerDelay = 25;

void setup() {
  // Set up Timer/Counter1 to multiplex the LEDs
  TCCR1 = 1<<CTC1 | 2<<CS10;          // Divide by 2
  GTCCR = 0;                          // No PWM
  OCR1A = 0;
  OCR1C = 250-1;                      // 16kHz
  TIMSK = TIMSK | 1<<OCIE1A;          // Compare Match A interrupt

  setupButton();
  setupLeds();

  for(int i=0; i<NUM_LEDS; i++) {
    candleFadeCounter[i] = candleFadeInit;
  }
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

int waitAndCheck (uint32_t time){
  for(int i=0; i<time; i++) {
    delay(1);
    if(checkButton()){
      return 1;
    }
  }
  return 0;
}

void loop () {
  srand(millis());
  for(int i=0; i<day; i++) {
    if(candleLevels[i] < baseBrightness) {
      candleLevels[i] = LogLevels[candleFadeCounter[i]];
      candleFadeCounter[i]++;
    } else {
      candleLevels[i] += ((rand() % variability) - variability/2);
      if(candleLevels[i] < baseBrightness) {
        candleLevels[i] = baseBrightness;
      } else if (candleLevels[i] > maxBrightness){
        candleLevels[i] = maxBrightness;
      }
    }
    setLed(i, candleLevels[i]);
  }
  if(waitAndCheck(flickerDelay)) {
    if(day < NUM_LEDS) {
      day ++;
    } else {
      day = 1;
      clearLeds();
      for(int i=0; i<NUM_LEDS; i++) {
        candleLevels[i] = 0;
        candleFadeCounter[i] = candleFadeInit;
      }
    }
  }
}