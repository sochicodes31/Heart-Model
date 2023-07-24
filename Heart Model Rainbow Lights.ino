#include <FastLED.h>

#define NUM_LEDS 6   // Number of LEDs in your strip
#define DATA_PIN 6   // Digital pin of your Arduino

CRGB leds[NUM_LEDS];

bool defaultMode = true; // Flag to indicate the default rainbow fade mode

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);  // Start the Serial communication
  
  // Start the default rainbow fade animation
  rainbowFade();
}

void loop() {
  if (Serial.available() > 0) {
    int input = Serial.parseInt(); // Read the serial input as an integer
    
    // Set the LED color based on the input value
    if (input >= 0 && input <= 10) {
      fadeToColor(CRGB::Green);
    } else if (input > 10 && input <= 20) {
      fadeToColor(CRGB::Yellow);
    } else if (input > 20 && input <= 30) {
      fadeToColor(CRGB::Red);
    } else if (input > 30 && input <= 40) {
      fadeToColor(CRGB::Purple);
    }
    
    // After receiving input, disable the default rainbow fade
    defaultMode = false;
  }
  
  // If not in input mode, run the default rainbow fade animation
  if (defaultMode) {
    rainbowFade();
  }
}

// Function to set the LED strip color
void setColor(CRGB targetColor) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = targetColor;
  }
  FastLED.show();
}

// Function to create a rainbow fade effect
void rainbowFade() {
  for (int hue = 0; hue < 255; hue += 5) {
    CRGB color = CHSV(hue, 255, 255); // Set color with varying hue
    fadeToColor(color);
  }
}

// Function to fade to the specified color
void fadeToColor(CRGB targetColor) {
  // Gradually fade the current color to the target color
  for (int i = 0; i < 256; i++) {
    CRGB currentColor = CRGB::Black;
    currentColor.nscale8(i);
    
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = blend(currentColor, targetColor, 128);
    }
    
    FastLED.show();
    delay(10);
  }
  
  // Set the LED strip to the target color
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = targetColor;
  }
  FastLED.show();
}


// Must press reset button after every test
