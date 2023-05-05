#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.setBrightness(60);
  strip.show();
}
void loop(){
  for(int i=0; i<100; i++)
  {
    if(i%2==0){
    strip.setPixelColor(i, 0,0,255);
    }
    else{
      strip.setPixelColor(i, 255,0,0);
    }
  }
  strip.show();
}
