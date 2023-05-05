#include <Adafruit_NeoPixel.h>
 
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(72, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  strip.setBrightness(60); 
  strip.show(); 
}    
   void odliczanie(){
  for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 0,0,255);
}
 
strip.show();
delay(50);} 
for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 0,128,255);
}
 
strip.show();
delay(50);}

for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 0,255,255);
}
 
strip.show();
delay(50);}

for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 0,255,128);
}
 
strip.show();
delay(50);
  }
 for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 0,255,0);
}
 
strip.show();
delay(50);
  }
  for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 128,255,0);
}
 
strip.show();
delay(50);
  }
  for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 255,255,0);
}
 
strip.show();
delay(50);
  }
  for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 255,128,0);
}
 
strip.show();
delay(50);
  }
  for(int i=0;i<100;i++)
  {
  if(i<100){
    strip.setPixelColor(i, 255,0,0);
}
 
strip.show();
delay(50);
  }
}
