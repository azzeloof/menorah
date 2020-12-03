#include "twinkle.h"

uint8_t randLeds[6] = {0, 0, 0, 0, 0, 0};
uint8_t currLevel[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t endLevel[6] = {0, 0, 0, 0, 0, 0};

void resetCurrVals()
{
    for(int i = 0; i < NUM_LEDS; i++)
    {
        currLevel[i] = 0;
    }
}

int runRampTwinkle(uint8_t numLeds, uint32_t msPerLevel)
{
    if(numLeds > 6) return 0;
    for(int i = 0; i < numLeds; i++)
    {
        if(randLeds[i] < 0 || randLeds[i] >= NUM_LEDS) return 0;
    }

    int8_t diff;
    uint8_t done = 0;
    unsigned long startTime = millis();
    unsigned long currTime;
    while(!done)
    {
        currTime = millis();
        if(currTime >= startTime + msPerLevel)
        {
            done = 1;
            startTime += msPerLevel;
            for(int i = 0; i < numLeds; i++)
            {
                if(currLevel[randLeds[i]] != endLevel[i])
                {
                    done = 0;
                    diff = endLevel[i] > currLevel[randLeds[i]] ? 1 : -1;
                    currLevel[randLeds[i]] += diff;
                    setLed(randLeds[i],currLevel[randLeds[i]]);
                }
                
            }
            
        }

        if (checkButton() != 0) 
        {
            resetCurrVals();
            return 1;
        }
    }

  return 0;

}

int hold(uint32_t holdTime)
{
    unsigned long currTime = millis();
    unsigned long endTime = currTime + holdTime;
    while(millis() < endTime)
    {
        if (checkButton() != 0)
        {
            resetCurrVals();
            return 1;
        }
    }

    return 0;
}

void twinkleProgram(uint32_t rampSpeed, uint32_t holdLength)
{
    srand(millis());

    uint8_t numLeds = (rand() % 6) + 1;
    for(int i = 0; i < numLeds; i++)
    {
        srand(millis());
        randLeds[i] = rand() % NUM_LEDS;
        endLevel[i] = (rand() % 63);
    }
    if(runRampTwinkle(numLeds, rampSpeed) != 0) return;

    //if(hold(holdLength) != 0) return;
}