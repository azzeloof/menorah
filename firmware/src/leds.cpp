#include "leds.h"

uint8_t Level[NUM_NODES];
uint8_t Order[NUM_LEDS];
uint8_t LogLevels[64] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,
                          1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  3,  3,
                          3,  4,  4,  4,  5,  5,  6,  7,  7,  8,  9, 10, 11, 12, 14, 15, 17,
                         18, 20, 23, 25, 28, 31, 34, 38, 42, 46, 51, 57, 63};

void initOrder() // middle first
{
    Order[0] = 11; //3
    Order[1] = 10; //0
    Order[2] = 1; //7
    Order[3] = 6; //4
    Order[4] = 8; //11
    Order[5] = 4; //8
    Order[6] = 7; //6
    Order[7] = 0; //1
    Order[8] = 3; //10
}

void setupLeds()
{
  initOrder();
  clearLeds(); 
}

void setLed(uint8_t led, uint8_t level)
{
  if(led >= 0 && led < NUM_LEDS)
  {
    if(level < 0) level = 0;
    if(level > 63) level = 63;
    Level[Order[led]] = LogLevels[level];

  }
}

void setLedLog(uint8_t led, uint8_t level)
{
  if(led >= 0 && led < NUM_LEDS)
  {
    if(level < 0) level = 0;
    if(level > 63) level = 63;
    Level[Order[led]] = level;
  }
}

void clearLeds()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    Level[Order[i]] = 0;
  }
}

void allOn()
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    Level[Order[i]] = 63;
  }
}