#include <FastLED.h>


#define _GAMMA_ 2.6
const int _GBASE_ = __COUNTER__ + 1; // Index of 1st __COUNTER__ ref below
#define _G1_ pow((__COUNTER__ - _GBASE_) / 255.0, _GAMMA_) * 255.0 + 0.5,
#define _G2_ _G1_ _G1_ _G1_ _G1_ _G1_ _G1_ _G1_ _G1_ // Expands to 8 items
#define _G3_ _G2_ _G2_ _G2_ _G2_ _G2_ _G2_ _G2_ _G2_ // Expands to 64 items
const uint8_t PROGMEM gammaTable[] = { _G3_ _G3_ _G3_ _G3_ }; // 256 items


struct LEDString {
  int pin;
  uint8_t offset;

  uint8_t animationAt(uint8_t progress8) {
    uint8_t offsetProgress = progress8 + offset;
    // Start at 0, go up to 255, then back down to 0.
    uint8_t animationValue = 255 - cos8(offsetProgress);
    return animationValue;
  }
};

LEDString ledStrings[6] = {
  { .pin = 3, .offset = 0 },
  { .pin = 5, .offset = (uint8_t)(255.0 * 1.0 / 6.0) },
  { .pin = 6, .offset = (uint8_t)(255.0 * 2.0 / 6.0) },
  { .pin = 9, .offset = (uint8_t)(255.0 * 3.0 / 6.0) },
  { .pin = 10, .offset = (uint8_t)(255.0 * 4.0 / 6.0) },
  { .pin = 11, .offset = (uint8_t)(255.0 * 5.0 / 6.0) },
};

void setup() {
  for (int i = 0; i < 6; ++i) {
    pinMode(ledStrings[i].pin, OUTPUT);
  }
}

uint8_t brightness = 0;
uint8_t brightnessIncrement = 1;

uint8_t gammaCorrect(uint8_t value) {
  return pgm_read_byte(&gammaTable[value]);
}

void loop() {
  delay(5);
  for (int i = 0; i < 6; ++i) {
    analogWrite(ledStrings[i].pin, gammaCorrect(ledStrings[i].animationAt(brightness)));
  }
  brightness += brightnessIncrement;
}
