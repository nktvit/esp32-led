#include <Adafruit_NeoPixel.h>

#define LED_PIN 12
#define LED_COUNT 95

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.show(); // initialize all pixels to off
}

void loop() {
  // put your main code here, to run repeatedly:
  sequentiallyLight();
  firstLight();
}

void sequentiallyLight() {
  for (int i = 1; i< LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(255,255,255));
  }
  strip.show();
  delay(3000);
}
void firstLight() {
  for (int i = 1; i< LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
   strip.setPixelColor(1, strip.Color(255,255,255));
   strip.show();
  delay(3000);
}