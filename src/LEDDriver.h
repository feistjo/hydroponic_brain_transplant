#include <Arduino.h>

class LEDDriver
{
public:
    LEDDriver(uint8_t led_left_outer, uint8_t led_right_inner, uint8_t led_inner) : kLedLeftOuter{led_left_outer}, kLedRightInner{led_right_inner}, kLedInner{led_inner}
    {
        pinMode(kLedLeftOuter, OUTPUT);
        pinMode(kLedRightInner, OUTPUT);
        pinMode(kLedInner, OUTPUT);
    }

    void SetLED(int8_t led_num)
    {
        if (0 <= led_num <= 3)
        {
            digitalWrite(kLedLeftOuter, kLedLUT[led_num][0]);
            digitalWrite(kLedRightInner, kLedLUT[led_num][1]);
            digitalWrite(kLedInner, kLedLUT[led_num][2]);
        }
        else
        {
            digitalWrite(kLedLeftOuter, LOW);
            digitalWrite(kLedRightInner, LOW);
            digitalWrite(kLedInner, LOW);
        }
    }

private:
    const uint8_t kLedLeftOuter;
    const uint8_t kLedRightInner;
    const uint8_t kLedInner;

    const bool kLedLUT[4][3] = {{1, 0, 0}, {0, 1, 1}, {1, 0, 1}, {0, 1, 0}};
};