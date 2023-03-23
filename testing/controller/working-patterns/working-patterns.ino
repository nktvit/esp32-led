#include <Adafruit_NeoPixel.h>
#include <time.h>

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
// Use current time as
    // seed for random generator
    srand(time(0));

  Serial.begin(115200);

  strip.begin();
  strip.show();

}

void loop() {
  //randomColorByGroups();
  sequential();
  // randomColorFillByAmount(5);
}



void randomColor() {
  static unsigned long previousMillis = 0;
  const uint8_t range = 255;
  static uint8_t pixel_num = 0;
  static uint8_t red = 0;
  static uint8_t green = 0;
  static uint8_t blue = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    strip.setPixelColor(pixel_num, strip.Color(0, 0, 0)); // turn off previous LED
    pixel_num = random(1, NUMPIXELS + 1); // generate random pixel number
    red = random(range + 1); // generate random color values
    green = random(range + 1);
    blue = random(range + 1);
    strip.setPixelColor(pixel_num, strip.Color(red, green, blue)); // set color of new LED
    strip.show();
  }
}

void randomColorFill() {
  static unsigned long previousMillis = 0;
  const uint8_t range = 255;
  static uint8_t pixel_num = 0;
  static uint8_t red[NUMPIXELS];
  static uint8_t green[NUMPIXELS];
  static uint8_t blue[NUMPIXELS];

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    for (int i = 0; i < NUMPIXELS; i++) {
      red[i] = random(range + 1); // generate random color values
      green[i] = random(range + 1);
      blue[i] = random(range + 1);
      strip.setPixelColor(i, strip.Color(red[i], green[i], blue[i])); // set color of LED
    }

    strip.show();
  }
}
void randomColorByGroups() {
  static unsigned long previousMillis = 0;
  const uint8_t range = 255;
  static uint8_t red[5];
  static uint8_t green[5];
  static uint8_t blue[5];

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 5 == 0) { // set new random color for each group of 5 LEDs
        for (int j = 0; j < 5; j++) {
          red[j] = random(range + 1);
          green[j] = random(range + 1);
          blue[j] = random(range + 1);
        }
      }
      strip.setPixelColor(i, strip.Color(red[i % 5], green[i % 5], blue[i % 5])); // set color of LED
    }

    strip.show();
  }
}

void randomColorFillByAmount(uint8_t amount) {
  static unsigned long previousMillis = 0;
  const uint8_t range = 255;
  static uint8_t group_num = 0;
  static uint8_t red[NUMPIXELS];
  static uint8_t green[NUMPIXELS];
  static uint8_t blue[NUMPIXELS];

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % amount == 0) { // set new random color for each group of amount LEDs
        red[i] = random(range + 1);
        green[i] = random(range + 1);
        blue[i] = random(range + 1);
      }
      strip.setPixelColor(i, strip.Color(red[i], green[i], blue[i])); // set color of LED
    }

    strip.show();
  }
}




void sequential() {
  static unsigned long previousMillis = 0;
  static int i = 2;
  static bool direction = true; // true for forward, false for backward
  static int hue = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 50) {
    previousMillis = currentMillis;

    if (direction) {
      strip.setPixelColor(i-2, strip.gamma32(strip.ColorHSV(hue + 120, 255, 50))); // set semi-darkened dot behind
      strip.setPixelColor(i-1, strip.gamma32(strip.ColorHSV(hue + 60, 255, 100))); // set dimmed dot behind
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue, 255, 255))); // set bright dot
      strip.setPixelColor(i+1, strip.gamma32(strip.ColorHSV(hue + 60, 255, 100))); // set dimmed dot in front
      strip.setPixelColor(i+2, strip.gamma32(strip.ColorHSV(hue + 120, 255, 50))); // set semi-darkened dot in front
    } else {
      strip.setPixelColor(i-2, strip.gamma32(strip.ColorHSV(hue + 120, 255, 50))); // set semi-darkened dot in front
      strip.setPixelColor(i-1, strip.gamma32(strip.ColorHSV(hue + 60, 255, 100))); // set dimmed dot in front
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue, 255, 255))); // set bright dot
      strip.setPixelColor(i+1, strip.gamma32(strip.ColorHSV(hue + 60, 255, 100))); // set dimmed dot behind
      strip.setPixelColor(i+2, strip.gamma32(strip.ColorHSV(hue + 120, 255, 50))); // set semi-darkened dot behind
    }

    hue += 500;
    if (hue >= 65536) {
      hue = 0;
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
