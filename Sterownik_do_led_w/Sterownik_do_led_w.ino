#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define BUTTON_PIN   2
#define BUTTON_PIN2   4

#define PIXEL_PIN    6 

Adafruit_NeoPixel strip(100, PIXEL_PIN, NEO_GRB + NEO_KHZ800);


boolean oldState = HIGH;
int     mode     = 0;    

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  strip.begin(); 
  strip.show();  
}

void loop() {
  
  boolean newState = digitalRead(BUTTON_PIN);

  if((newState == LOW) && (oldState == HIGH)) {
 
    delay(20);
   
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {     
      if(++mode > 5) mode = 0; 
      switch(mode) {          
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 30);
          break;
        case 1:
          colorWipe(strip.Color(255,   0,   0), 30);
          break;
        case 2:
          colorWipe(strip.Color(  0, 255,   0), 30);
          break;
        case 3:
          colorWipe(strip.Color(  0,   0, 255), 30);
          break;
        case 4:
          for(int i=0;i<100;i++){
          rainbow();}
          break; 
      }
    }
  }
  
  oldState = newState;
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                           
  }
}

void rainbow(){
   //rainbow(20);
  rainbowCycle(20);
}
 
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
