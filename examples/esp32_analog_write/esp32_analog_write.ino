// esp32_analog_write.ino
// klin, 30.03.2020
// example: fade a led using analogWrite on ESP32

#include "ESP32AnalogWrite.h"

// led on gpio 14
const int led = 14;

// setup
void setup()
{
  Serial.begin(115200);
  Serial.println("start led fading on esp32");
}

// loop
void loop()
{
  // fade up
  for(int v = 0; v < 255; v += 2) {
    analogWrite(led, v);
    delay(20);  
  }
  for(int v = 255; v >= 0; v -= 2) {
    analogWrite(led, v);
    delay(20);
  }
}
