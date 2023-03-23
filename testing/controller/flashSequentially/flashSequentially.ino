#include <Adafruit_NeoPixel.h>

#define LED_PIN 12 // GPOI 12
#define LED_COUNT 95

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // all pixels to off
}

void loop() {
  flashSequentially();
}


void flashSequentially() {
  // Set all the pixels to off
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();

  int start = 0;
  int end = LED_COUNT - 1;

  while (true) {
    // Flash from start to end
    for (int i = start; i <= end; i++) {
      strip.setPixelColor(i, strip.Color(11, 99, 40));
    }
    strip.show();
    delay(5);

    for (int i = start; i <= end; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(5);

    // Flash from end to start
    for (int i = end; i >= start; i--) {
      strip.setPixelColor(i, strip.Color(11, 99, 40));
    }
    strip.show();
    delay(5);

    for (int i = end; i >= start; i--) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(5);

    // Increment start and decrement end
    start++;
    end--;

    // Reset start and end if they exceed the number of pixels
    if (start >= LED_COUNT) {
      start = 0;
    }
    if (end < 0) {
      end = LED_COUNT - 1;
    }
  }
}

