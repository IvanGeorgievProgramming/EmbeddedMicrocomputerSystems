// * Importing Libraries

#include <Arduino.h>
#include <FastLED.h>

// * Defining Variables

#define NUM_LEDS  60
#define LED_PIN   13

CRGB leds[NUM_LEDS];

// * Defining Palletes

uint8_t paletteIndex = 0;

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
	0,   120, 0,   0,
	22,  179, 22,  0,
	51,  255, 104, 0,
	85,  167, 22,  18,
  	135, 100, 0,   103,
  	198, 16,  0,   130,
  	255, 0,   0,   160
};


CRGBPalette16 myPal = Sunset_Real_gp;

// * Defining Functions

void setBrightness(int brightness);
void setColorCorrection(int colorCorrectionOption);
void setTemperature(int temperatureOption);
void setLedRGB(int r, int g, int b, int ledId);
void setLedHSV(int h, int s, int v, int ledId);
void blinkLedRGB(int ledId, int speed, int r, int g, int b);
void blinkLedHSV(int ledId, int speed, int h, int s, int v);

void setLedRGBFunction(int r, int g, int b);
void setLedHSVFunction(int h, int s, int v);
void moveLedRGBFunction(int led, int speed, int r, int g, int b);
void moveLedHSVFunction(int led, int speed, int h, int s, int v);
void blinkEveryNthLedRGBFunction(int Nth, int speed, int r, int g, int b);
void blinkEveryNthLedHSVFunction(int Nth, int speed, int h, int s, int v);

void rainbowFunction();
void rainbowBeatFunction();
void phaseBeatFunction();
void sunsetPaletteFunction();

// * Setup and Loop

void setup() {
  
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness(150);

	Serial.begin(9600);

	FastLED.clear(true);
}

void loop () {
	sunsetPaletteFunction();
}

// * Functions

void setBrightness(int brightness) {
  	FastLED.setBrightness(brightness);
}

void setColorCorrection(int colorCorrectionOption){
	switch(colorCorrectionOption) {
		case 0:
			FastLED.setCorrection(TypicalLEDStrip);
			break;
		case 1:
			FastLED.setCorrection(TypicalSMD5050);
			break;
		case 2:
			FastLED.setCorrection(Typical8mmPixel);
			break;
		case 3:
			FastLED.setCorrection(UncorrectedColor);
			break;
	}
}

void setTemperature(int temperatureOption){
	switch(temperatureOption) {
		case 0:
			FastLED.setTemperature(Candle);
			break;
		case 1:
			FastLED.setTemperature(Tungsten40W);
			break;
		case 2:
			FastLED.setTemperature(Tungsten100W);
			break;
		case 3:
			FastLED.setTemperature(Halogen);
			break;
		case 4:
			FastLED.setTemperature(CarbonArc);
			break;
		case 5:
			FastLED.setTemperature(HighNoonSun);
			break;
		case 6:
			FastLED.setTemperature(DirectSunlight);
			break;
		case 7:
			FastLED.setTemperature(OvercastSky);
			break;
		case 8:
			FastLED.setTemperature(ClearBlueSky);
			break;
	}
}

void setLedRGB(int r, int g, int b, int ledId) {
  	leds[ledId] = CRGB(r, g, b);
  	FastLED.show();
}

void setLedHSV(int h, int s, int v, int ledId) {
  	leds[ledId] = CHSV(h, s, v);
  	FastLED.show();
}

void blinkLedRGB(int ledId, int speed, int r, int g, int b) {
  	setLedRGB(r, g, b, ledId);
  	delay(speed);
  	setLedRGB(0, 0, 0, ledId);
  	delay(speed);
}

void blinkLedHSV(int ledId, int speed, int h, int s, int v) {
  	setLedHSV(h, s, v, ledId);
  	delay(speed);
  	setLedHSV(0, 0, 0, ledId);
  	delay(speed);
}



void setLedRGBFunction(int r, int g, int b){
	for(int i = 0; i < NUM_LEDS; i++) {
		setLedRGB(r, g, b, i);
  	}
}

void setLedHSVFunction(int h, int s, int v){
	for(int i = 0; i < NUM_LEDS; i++) {
		setLedHSV(h, s, v, i);
  	}
}

void moveLedRGBFunction(int led, int speed, int r, int g, int b){
	for(int i = 0; i < NUM_LEDS; i++) {
		setLedRGB(r, g, b, i);
		delay(speed);
		leds[i] = CRGB::Black;
  	}

  	for(int i = NUM_LEDS - 1; i >= 0; i--) {
		setLedRGB(r, g, b, i);
		delay(speed);
		leds[i] = CRGB::Black;
  	}
}

void moveLedHSVFunction(int led, int speed, int h, int s, int v){
	for(int i = 0; i < NUM_LEDS; i++) {
		setLedHSV(h, s, v, i);
		delay(speed);
		leds[i] = CRGB::Black;
  	}

  	for(int i = NUM_LEDS - 1; i >= 0; i--) {
		setLedHSV(h, s, v, i);
		delay(speed);
		leds[i] = CRGB::Black;
  	}
}

void blinkEveryNthLedRGBFunction(int Nth, int speed, int r, int g, int b){
	for(int i = 0; i < NUM_LEDS; i++) {
		if(i % Nth == 0) {
			blinkLedRGB(i, speed, r, g, b);
		}
  	}
}
void blinkEveryNthLedHSVFunction(int Nth, int speed, int h, int s, int v){
	for(int i = 0; i < NUM_LEDS; i++) {
		if(i % Nth == 0) {
			blinkLedHSV(i, speed, h, s, v);
		}
  	}
}



void rainbowFunction(){
	fill_rainbow(leds, NUM_LEDS, 0, 8);
	
	FastLED.show();
}
void rainbowBeatFunction(){
	uint16_t beatA = beatsin16(30, 0, 255);
    uint16_t beatB = beatsin16(20, 0, 255);
    fill_rainbow(leds, NUM_LEDS, (beatA + beatB)/2, 8);
    
    FastLED.show();
}

void phaseBeatFunction(){
	uint8_t sinBeat   = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
  	uint8_t sinBeat2  = beatsin8(30, 0, NUM_LEDS - 1, 0, 85);
  	uint8_t sinBeat3  = beatsin8(30, 0, NUM_LEDS - 1, 0, 170);

  	leds[sinBeat]   = CRGB::Blue;
  	leds[sinBeat2]  = CRGB::Red;
  	leds[sinBeat3]  = CRGB::White;
  
  	fadeToBlackBy(leds, NUM_LEDS, 10);

  	EVERY_N_MILLISECONDS(10){
    	Serial.print(sinBeat);
    	Serial.print(",");
    	Serial.print(sinBeat2);
    	Serial.print(",");
    	Serial.println(sinBeat3);
  	}

  	FastLED.show();
}

void sunsetPaletteFunction(){
	fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, myPal, 255, LINEARBLEND);
  
  	EVERY_N_MILLISECONDS(10){
    	paletteIndex++;
  	}
  
  	FastLED.show();
}