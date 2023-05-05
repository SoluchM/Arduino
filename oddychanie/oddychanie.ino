#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(84, PIN, NEO_GRB + NEO_KHZ800);

void setup (){
    strip.begin();
  strip.show();
}

void loop(){
  strip.setPixelColor(50, 0,0,255);
    strip.show();
  for(int i=0;i<84;i++)
  {
     
    
    
    strip.setBrightness(0);
delay(5);

    strip.setBrightness(30);
delay(5);

     strip.setBrightness(60);
delay(5);

    strip.setBrightness(50);
delay(5);

     strip.setBrightness(40);
delay(5);

    strip.setBrightness(30);
delay(5);

     strip.setBrightness(20);
delay(5);

    strip.setBrightness(10);
delay(5);

    strip.setBrightness(0);
delay(5);
    
  }
}
