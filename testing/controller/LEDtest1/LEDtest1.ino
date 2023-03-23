#include <Adafruit_NeoPixel.h>

// What pin on the ESP32-WROOM-32 is connected to the LED (WS2812C-2020)
#define PIN 12 // GPIO12 output

// How many NeoPixels are attached to the board?
#define NUMPIXELS 95 // 2m, 144led/m

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

int j = 0;


void setup() {
  Serial.begin(115200);

  strip.begin();
  strip.show();

}

void loop() {
  sequential();
  //thunder(100);
  //flash(100);
// colorWipe(0xFF0000, 50);
// theaterChase(0xFF9C3D, 0xFFFFFF, 0x0EBD00, 50);

}

void sequential() {
  static unsigned long previousMillis = 0;
  static int i = 2;
  static bool direction = true; // true for forward, false for backward

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 50) {
    previousMillis = currentMillis;

    if (direction) {
      strip.setPixelColor(i-2, strip.Color(64, 64, 64)); // set semi-darkened dot behind
      strip.setPixelColor(i-1, strip.Color(128, 128, 128)); // set dimmed dot behind
      strip.setPixelColor(i, strip.Color(255, 255, 255)); // set bright dot
      strip.setPixelColor(i+1, strip.Color(128, 128, 128)); // set dimmed dot in front
      strip.setPixelColor(i+2, strip.Color(64, 64, 64)); // set semi-darkened dot in front
    } else {
      strip.setPixelColor(i-2, strip.Color(64, 64, 64)); // set semi-darkened dot in front
      strip.setPixelColor(i-1, strip.Color(128, 128, 128)); // set dimmed dot in front
      strip.setPixelColor(i, strip.Color(255, 255, 255)); // set bright dot
      strip.setPixelColor(i+1, strip.Color(128, 128, 128)); // set dimmed dot behind
      strip.setPixelColor(i+2, strip.Color(64, 64, 64)); // set semi-darkened dot behind
    }

    i += direction ? 1 : -1;
    if (i == NUMPIXELS) {
      direction = false;
      i = NUMPIXELS - 2;
    } else if (i == 1) {
      direction = true;
      i = 2;
    }

    strip.show();
  }
}


void rainbow(int j) {
  int k = 0;
  int l = 0;
  int m = 0;

  for (int i = 0; i < NUMPIXELS; i++) {
    if ((i >= 0) && (i < NUMPIXELS * 1 / 3)) {
      red = 255 * k / (NUMPIXELS / 3);
      green = 0;
      blue = 255 - (255 * k / (NUMPIXELS / 3));
      k++;
    }
    if ((i >= NUMPIXELS * 1 / 3) && (i < NUMPIXELS * 2 / 3)) {
      red = 255 - (255 * l / (NUMPIXELS / 3));
      green = 255 * l / (NUMPIXELS / 3);
      blue = 0;
      l++;
    }
    if ((i >= NUMPIXELS * 2 / 3) && (i < NUMPIXELS * 3 / 3)) {
      red = 0;
      green = 255 - (255 * m / (NUMPIXELS / 3));
      blue = 255 * m / (NUMPIXELS / 3);
      m++;
    }

    strip.setPixelColor((i + j) % NUMPIXELS, strip.Color(red, green, blue));
  }

  strip.show();
  delay(50);
}

void colorWipe(uint32_t color, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t color1, uint32_t color2, uint32_t color3, uint8_t wait) {
  for (int j = 0; j < 10; j++) {  // Repeat the loop 10 times
    for (int k = 0; k < 3; k++) {  // Loop through each color
      for (uint16_t i = k; i < strip.numPixels(); i += 3) {
        strip.setPixelColor(i, color1);  // Set the color of every third LED to color1
      }
      strip.show();
      delay(wait);
      for (uint16_t i = k; i < strip.numPixels(); i += 3) {
        strip.setPixelColor(i, color2);  // Set the color of every third LED to color2
      }
      strip.show();
      delay(wait);
      for (uint16_t i = k; i < strip.numPixels(); i += 3) {
        strip.setPixelColor(i, color3);  // Set the color of every third LED to color3
      }
      strip.show();
      delay(wait);
    }
  }
}

void thunder(uint8_t wait) {
  // Loop through each LED in the strip
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    // Set the color of the current LED to white
    strip.setPixelColor(i, strip.Color(50, 50, 50));
    strip.show();       // Display the updated color on the strip
    delay(wait);        // Wait for a short time before updating the next LED
  }
  // Loop through each LED in the strip in reverse order
  for (uint16_t i = strip.numPixels() - 1; i >= 0; i--) {
    // Set the color of the current LED to black (turn off)
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();       // Display the updated color on the strip
    delay(wait);        // Wait for a short time before updating the next LED
  }
}

void flash(uint16_t wait) {
  // Set all LEDs to white
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(50, 50, 50));
  }
  strip.show();         // Display the updated colors on the strip
  delay(wait);          // Wait for a short time before flashing off
  // Set all LEDs to black (turn off)
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();         // Display the updated colors on the strip
  delay(wait);          // Wait for a short time before starting again
}

