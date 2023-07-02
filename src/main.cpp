#include <Arduino.h>
#include "LEDDriver.h"

const uint8_t kTouchPins[] = {12, 13, 15, 2};
uint8_t touch_pin_thresholds[4];
bool pins_touched[] = {false, false, false, false};

LEDDriver indicator_leds{0, 4, 9};

const uint8_t kRedWhiteLEDPin{10};
const uint8_t kBlueLEDPin{5};
const uint8_t kPumpPin{18};

const uint8_t kBuzzerPin{23};

uint8_t indicator_led = 4;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(kRedWhiteLEDPin, OUTPUT);
  pinMode(kBlueLEDPin, OUTPUT);
  pinMode(kPumpPin, OUTPUT);
  pinMode(kBuzzerPin, OUTPUT);
  for (int i = 0; i < 4; i++)
  {
    touch_pin_thresholds[i] = touchRead(kTouchPins[i]) - 2;
  }
}

void PrintTouchedPins()
{
  Serial.print("Touched pins:");
  for (int i = 0; i < 4; i++)
  {
    Serial.printf(" %d:  %d,", kTouchPins[i], touchRead(kTouchPins[i]) /* pins_touched[i] ? "Y" : "N" */);
  }
  Serial.println();
}

void loop()
{
  indicator_leds.SetLED(indicator_led);
  indicator_led++;
  if (indicator_led > 4)
  {
    indicator_led = 0;
  }
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 4; i++)
  {
    pins_touched[i] = touchRead(kTouchPins[i]) < 50;
  }
  PrintTouchedPins();
  digitalWrite(kRedWhiteLEDPin, HIGH);
  digitalWrite(kBlueLEDPin, HIGH);
  digitalWrite(kPumpPin, HIGH);
  tone(kBuzzerPin, 220);
  delay(500);
  digitalWrite(kRedWhiteLEDPin, LOW);
  digitalWrite(kBlueLEDPin, LOW);
  digitalWrite(kPumpPin, LOW);
  noTone(kBuzzerPin);
  delay(500);
}