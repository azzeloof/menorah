#include "modeButton.h"

#define BUTTON_PIN 0
#define DEBOUNCE_DELAY 1

uint8_t mode;
uint8_t lastButtonState = LOW;
uint8_t buttonState = LOW;
unsigned long lastDebounceTime = 0;

void setupButton()
{
    pinMode(BUTTON_PIN, INPUT);
    mode = 0;
}

int checkButton()
{
  uint8_t reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle if the new button state is HIGH
      if (buttonState == HIGH) {
        mode = (mode + 1) % NUM_MODES;
        clearLeds();
        return 1;
      }
    }
  }

  return 0;
}