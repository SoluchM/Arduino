#include "FastLED.h"
#define LED_PIN 8
#define NUM_LEDS 100
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  64 


CRGB leds[NUM_LEDS];

void setup() {
  LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  }
  
uint8_t gHue = 0; 

void loop() {
    //beatsin16 is a function on the FastLED library generating sinwave, (5) is bpm, (0,255) is value range.
    //value range will create the breathing effect 
    int pos = beatsin16(5,0,192); // generating the sinwave 
    fill_solid(leds, NUM_LEDS, CHSV( gHue, 255, pos)); // CHSV (hue, saturation, value);
    FastLED.show();
    EVERY_N_MILLISECONDS(100) {gHue++;} 
    // shifting the HUE value by incrementing every millisecond this creates the spectrum wave

    /* spectrum wave
     * fill_solid(leds, NUM_LEDS, CHSV( gHue, 255, 255)); // remove pos
     * FastLED.show();
     * EVERY_N_MILLISECONDS(100) {gHue++;} 
     */
     //additional codes, just to share
    /* color spectrum generator
     *  fill_rainbow( leds, NUM_LEDS, gHue, 3);
     */
}
