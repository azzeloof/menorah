#include "chaos.h"

int holdchaos(uint32_t delayTime)
{
    unsigned long startTime = millis();

    while((millis() - startTime) < delayTime)
    {
        if(checkButton() != 0) return 1;
    }

    return 0;
}

void chaosProgram(uint32_t holdOn, uint32_t holdOff)
{
    srand(millis());
    uint8_t randLed = rand() % 12;
    setLed(randLed, 63);

    if(holdchaos(holdOn) != 0) return;

    setLed(randLed, 0);

    holdchaos(holdOff);
}