#include <Arduino.h> 
#include <FastLED.h>

#define NUM_LEDS 60
#define LEDS_PIN 13

CRGB leds[NUM_LEDS];

void setup() {
	// put your setup code here, to run once:
	FastLED.addLeds<WS2812B, LEDS_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness(255);
}

void loop() {
	// put your main code here, to run repeatedly:
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CRGB::Red;
		FastLED.show();
		delay(100);
	}

	for (int i = NUM_LEDS - 1; i >= 0; i--) {
		leds[i] = CRGB::Black;
		FastLED.show();
		delay(100);
	}
}