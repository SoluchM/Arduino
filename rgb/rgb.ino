#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.setBrightness(60);
  strip.show();
}
void loop(){
  for(int i=0;i <100 ;i++) // Zapalenie całego paska na czerwono
   {
      strip.setPixelColor(i, 150, 0, 0);
   }
 
   strip.show();
   delay(1000);
   
   for(int i=0;i <100 ;i++) // Zapalenie całego paska na niebiesko 
   {
      strip.setPixelColor(i, 0, 0, 150);   
   }
 
   strip.show();
   delay(1000);  
   
   for(int i=0;i <100 ;i++) // Zapalenie całego paska na zielono
   {
      strip.setPixelColor(i, 0, 150, 0);
   }
 
   strip.show();
   delay(1000);  
}
 
