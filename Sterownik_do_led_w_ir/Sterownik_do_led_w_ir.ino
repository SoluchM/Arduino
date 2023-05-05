#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
#define irPin 11
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);
IRrecv irrecv(irPin);
decode_results results;
int     mode     = 0;
void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
 if (irrecv.decode(&results)){
  switch (results.value){
  
  case 0xFF1AE5:
   colorWipe(strip.Color(255,   0,   0), 30);
  
       break;

    case 0xFF9A65:
   
    colorWipe(strip.Color(  0, 255,   0), 30);
    
    
    break;

    case 0xFFA25D:
    
    colorWipe(strip.Color(  0,   0, 255), 30);
    
    
    break;
    case 0xFF22DD:

    colorWipe(strip.Color( 255,255,255),30);

    break;

  }
  irrecv.resume();
 }

}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<300; i++) { 
    strip.setPixelColor(i, color);  
    strip.setBrightness(60);       
    strip.show();                          
    delay(wait);                        
  }
}
