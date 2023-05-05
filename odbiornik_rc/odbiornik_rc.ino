#include <IRremote.h>
#define irPin 11

IRrecv irrecv(irPin);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("0x");
    Serial.println(results.value, HEX);
    delay(500);
    irrecv.resume();
  }
}
