#include <Arduino.h>
#include <time.h>
//trying https://www.electronicshub.org/esp32-bluetooth-tutorial/
#include "BluetoothSerial.h"
#include "LEDDriver.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// TODO: type issues w/ "enum class" instead of "enum"; need to investigate options
enum Pin : uint8_t 
{
  kPowerButton = 12,
  kVegButton = 13,
  kFlowerButton = 15,
  kPumpButton = 2,
  kRedWhiteLED = 10,
  kBlueLED = 5,
  kPump = 18,
  kBuzzer = 23,
  kButtonLEDLeftOuter = 0,
  kButtonLEDRightInner = 4,
  kButtonLEDInner = 9
};

BluetoothSerial SerialBT;
time_t timeOrigin = time(NULL);
const int pumpOnDuration{1800};  // seconds
const int pumpOffDuration{1800}; // seconds
int lightsOnTime = 0; //seconds after midnight -- for now, "midnight" will be start time of chip
int lightsOnDuration = 57600; //seconds

const uint8_t kPowerButtonPin{12};
const uint8_t kVegButtonPin{13};
const uint8_t kFlowerButtonPin{15};
const uint8_t kPumpButtonPin{2};
const Pin kTouchPins[] = {Pin::kPowerButton, Pin::kVegButton, Pin::kFlowerButton, Pin::kPumpButton};
uint8_t touch_pin_thresholds[4];
bool pins_touched[] = {false, false, false, false};

// Time to turn lights on and off every day. Year, month, and day are ignored for on_time and off_time
time_t on_time = ;
time_t off_time = ;

LEDDriver indicator_leds{Pin::kButtonLEDLeftOuter, Pin::kButtonLEDRightInner, Pin::kButtonLEDInner};
//LEDDriver indicator_leds{0, 4, 9};

const uint8_t kRedWhiteLEDPin{10};
const uint8_t kBlueLEDPin{5};
const uint8_t kPumpPin{18};

const uint8_t kBuzzerPin{23};

uint8_t indicator_led = 4;

void gotTouch1(){
  pins_touched[0] = true;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin();
  Serial.println("Bluetooth started! Ready to pair...");
  pinMode(kRedWhiteLEDPin, OUTPUT);
  pinMode(kBlueLEDPin, OUTPUT);
  pinMode(kPumpPin, OUTPUT);
  pinMode(kBuzzerPin, OUTPUT);
  for (int i = 0; i < 4; i++)
  {
    touch_pin_thresholds[i] = touchRead(kTouchPins[i]) - 2;
  }
  //touchAttachInterrupt();
  xTaskCreate();
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
  //indicator_leds.SetLED(indicator_led);
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
  //digitalWrite(kRedWhiteLEDPin, HIGH);
  //digitalWrite(kBlueLEDPin, HIGH);
  //digitalWrite(kPumpPin, HIGH);
  //tone(kBuzzerPin, 220);
  delay(500);
  digitalWrite(kRedWhiteLEDPin, LOW);
  digitalWrite(kBlueLEDPin, LOW);
  //digitalWrite(kPumpPin, LOW);
  //noTone(kBuzzerPin);
  delay(500);
  while (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  while (SerialBT.available())
  {
    Serial.write(SerialBT.read());
  }
}

class TouchButton
{

};