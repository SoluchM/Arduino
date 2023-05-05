#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(10);
}

void loop() {
 int i = 0;
  for (i = 0; i < 300; i++) {  
    strip.setPixelColor(i, strip.Color(255, 0, 0)); 
  }
  
 strip.show();
  delay(200);
 
   for (i = 0; i < 300; i++) {  
    strip.setPixelColor(i, strip.Color(0, 0, 255)); 
  }
  
 strip.show(); 
  delay(200);  
}
