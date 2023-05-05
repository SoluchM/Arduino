#include <Adafruit_NeoPixel.h>
 
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(72, PIN, NEO_GRB + NEO_KHZ800);
void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}
void loop() {
  RGBLoop();
}
void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < 120; i++ ) {
    setPixel(i, red, green, blue);
  }
  show.strip();
}
void RGBLoop(){
  for(int j = 0; j < 3; j++ ) {
    // Fade IN
    for(int k = 0; k < 256; k++) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      show.strip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      show.strip();
      delay(3);
      
    }
  }
}
