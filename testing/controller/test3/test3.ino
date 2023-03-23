#include <Adafruit_NeoPixel.h>
#define PIN        12
#define NUMPIXELS 288

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 288; i++) {
    pixels.setPixelColor(i, pixels.Color(155, 155, 155));
  }
  
  pixels.show();
  delay(2000);
  pixels.clear();
  delay(1000);
}
