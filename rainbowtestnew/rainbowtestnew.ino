#include <Adafruit_NeoPixel.h>
#define PIN 6
class Strip
{
public:
  uint8_t   effect;
  uint8_t   effects;
  uint16_t  effStep;
  unsigned long effStart;
  Adafruit_NeoPixel strip;
  Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype) {
    effect = -1;
    effects = toteffects;
    Reset();
  }
  void Reset(){
    effStep = 0;
    effect = (effect + 1) % effects;
    effStart = millis();
  }
};

struct Loop
{
  uint8_t currentChild;
  uint8_t childs;
  bool timeBased;
  uint16_t cycles;
  uint16_t currentTime;
  Loop(uint8_t totchilds, bool timebased, uint16_t tottime) {currentTime=0;currentChild=0;childs=totchilds;timeBased=timebased;cycles=tottime;}
};

Strip strip_0(60, 8, 60, NEO_GRB + NEO_KHZ800);
struct Loop strip0loop0(1, false, 1);
struct Loop strip0loop00(1, false, 1);

//[GLOBAL_VARIABLES]

void setup() {

  //Your setup here:

  strip_0.strip.begin();
}

void loop() {

  //Your code here:

  strips_loop();
}

void strips_loop() {
  if(strip0_loop0() & 0x01)
    strip_0.strip.show();
}

uint8_t strip0_loop0() {
  uint8_t ret = 0x00;
  switch(strip0loop0.currentChild) {
    case 0: 
           ret = strip0_loop00();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(strip0loop0.currentChild + 1 >= strip0loop0.childs) {
      strip0loop0.currentChild = 0;
      if(++strip0loop0.currentTime >= strip0loop0.cycles) {strip0loop0.currentTime = 0; ret |= 0x02;}
    }
    else {
      strip0loop0.currentChild++;
    }
  };
  return ret;
}

uint8_t strip0_loop00() {
  uint8_t ret = 0x00;
  switch(strip0loop00.currentChild) {
    case 0: 
           ret = strip0_loop00_eff0();break;
  }
  if(ret & 0x02) {
    ret &= 0xfd;
    if(strip0loop00.currentChild + 1 >= strip0loop00.childs) {
      strip0loop00.currentChild = 0;
      if(++strip0loop00.currentTime >= strip0loop00.cycles) {strip0loop00.currentTime = 0; ret |= 0x02;}
    }
    else {
      strip0loop00.currentChild++;
    }
  };
  return ret;
}

uint8_t strip0_loop00_eff0() {
    // Strip ID: 0 - Effect: Move - LEDS: 60
    // Steps: 60 - Delay: 50
    // Colors: 0 ()
    // Options: toLeft=false, rotate=true, 
  if(millis() - strip_0.effStart < 50 * (strip_0.effStep)) return 0x00;
  uint32_t c = strip_0.strip.getPixelColor(59);
  for(uint16_t j=60-1;j>0;j--) 
    strip_0.strip.setPixelColor(j, strip_0.strip.getPixelColor(j-1)); 
  strip_0.strip.setPixelColor(0, c); 
  if(strip_0.effStep >= 60) {strip_0.Reset(); return 0x03; }
  else strip_0.effStep++;
  return 0x01;
}
