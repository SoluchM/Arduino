#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(84, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show();
}
void loop() {
  for(int i=0;i<84;i++)
  {
    if(i<84){
    strip.setPixelColor(i, 0,0,255);
    strip.show();
    
    }
    if(i<84){
    strip.setPixelColor(i+1, 0,0,255);
    strip.show();
    
    }
     if(i<84){
    strip.setPixelColor(i+2, 0,0,255);
    strip.show();
    
    }
     if(i<84){
    strip.setPixelColor(i+3, 0,0,255);
    strip.show();
    
    }
     if(i<84){
    strip.setPixelColor(i+4, 0,0,255);
    strip.show();
    
    }
     if(i<84){
    strip.setPixelColor(i+5, 0,0,255);
    strip.show();
    
     }
       if(i<84){
    strip.setPixelColor(i+6, 0,0,255);
    strip.show();
       }
     if(i<84){
    strip.setPixelColor(i, 0,0,0);
    strip.show();
    
    }
  }
  
}
