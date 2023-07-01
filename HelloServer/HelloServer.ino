#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>

#define PIN D4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);
#ifndef STASSID
#define STASSID "***********"
#define STAPSK  "************"
#endif


const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  String message = "<html><head></head><body style='font-family: sans-serif; font-size: 12px'>Following functions are available:<br><br>";
  message += "<a href='/rainbow?fade=3000'>/rainbow</a> a rainbow animation on LEDs<br>";
  message += "<a href='/wave?r=255&g=32&b=10&fade=5000'>/wave</a> a slow wave animation on LED on base color specified by arguments: r=<0..255> g=<0..255> b=<0..255><br>";
  message += "<a href='/setleds?r=32&g=64&b=32&fade=1000'>/setleds</a> sets LEDs to the color from arguments: r=<0..255> g=<0..255> b=<0..255><br>";
  message += "<a href='/ledsoff?fade=500'>/ledsoff</a> turns off LEDs<br>";
  message += "<a href='/setpins?D1=128&D2=256&D3=512'>/setpins</a> sets to any of the in arguments specified pins (D0..D8) to their PWM values (0..1023). To use them digital: 0=off, 1023=on<br>";
  message += "<a href='/togglepins'>/togglepins</a> inverts all pin values form pins used before.<br>";
  message += "<a href='/rf?D=6&t=200&id=28013&channel=0&on=1'>/rf</a> sends a rf code from arguments: D=<0..8> t=<0..1000> id=<0..1048575> channel=<0..2> on=<0..1>. Dx is the pin, t is the optional signal clock(default is 200, works for me)<br><br>";
  message += "All functions except togglepins and rf support the argument 'fade' which specifies the milliseconds it takes to fade to the new specified state. ...nice blending ;-)<br>";
  message += "<br>Syntax is as follows: http://&ltip>/&ltcommand>?&ltargument1>=&ltvalue1>&&ltargument2>=&ltvalue2>&...<br>";
  message += "You can click on each link to see an example.<br><br>";
  message += "have fun -<a href='http://youtube.com/bitlunislab'>bitluni</a></body></html>";
  server.send(200, "text/html", message);
}

void handleNotFound() {
  digitalWrite(led, 0);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/rainbow", [](){
    server.send(200, "text/plain", "rainbow");
    checkFadeAndSetLedFunction(new RainbowFunction());
  });

  server.on("/wave", [](){
    server.send(200, "text/plain", "wave");
    WaveFunction *f = new WaveFunction();
    f->init(server);
    checkFadeAndSetLedFunction(f);
  });

  server.on("/setleds", [](){
    server.send(200, "text/plain", "setleds");
    SimpleRGBFunction *f = new SimpleRGBFunction();
    f->init(server);
    checkFadeAndSetLedFunction(f);
  });

  server.on("/ledsoff", [](){
    server.send(200, "text/plain", "ledsoff");
    checkFadeAndSetLedFunction(new SimpleRGBFunction());
  });

  server.on("/togglepins", [](){
    server.send(200, "text/plain", "togglepins");
    currentPinStates.toggle();
    currentPinStates.commit();
  });
  
  server.on("/setpins", [](){
    server.send(200, "text/plain", "setpins");
    int fade = getArgValue("fade");
    if(fade > -1)
    {
      targetPinStates.loadValues(server);
      pinFader.start(fade);
    }
    else
    {
      currentPinStates.loadValues(server);
      currentPinStates.commit();
    }
  });

  server.on("/pinsoff", [](){
    server.send(200, "text/plain", "pinsoff");
    currentPinStates.setAllTo(0);
    currentPinStates.commit();
  });

  server.on("/rf", handleRf);
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(void)
{
  server.handleClient();
  //MDNS.update();
  currentLedStates.render();
  if(ledFader.active)
    targetLedStates.render();
  if(!ledFader.fade())
    currentLedStates.commit();
  pinFader.fade();
}
