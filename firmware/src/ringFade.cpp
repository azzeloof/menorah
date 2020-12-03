#include "ringFade.h"

uint8_t outerLeds[6] = {0,1,2,3,4,5};

int runRampRing(uint8_t numLeds, int8_t startLevel, int8_t endLevel, int32_t rampTime)
{
  int8_t diff = endLevel > startLevel ? 1 : -1;
  uint32_t msPerLevel = rampTime / (endLevel - startLevel) * diff;

  uint8_t currValue = startLevel;
  unsigned long currTime;
  unsigned long startTime = millis();
  while(currValue != endLevel)
  {
    currTime = millis();
    if(currTime >= startTime + msPerLevel)
    {
      startTime += msPerLevel;
      currValue += diff;
      for(uint8_t i = 0; i < numLeds; i++)
      {
        setLed(outerLeds[i], currValue);
        if( endLevel > startLevel) setLed(outerLeds[i] + numLeds, endLevel - currValue);
        else setLed(outerLeds[i] + numLeds, startLevel - currValue);
      }
    }

    if (checkButton() != 0) return 1;
  }

  return 0;

}

void fadeProgram()
{
  if(runRampRing(6, 0, 63, 2500) != 0) return;
  if(runRampRing(6, 63, 0, 2500) != 0) return;
}