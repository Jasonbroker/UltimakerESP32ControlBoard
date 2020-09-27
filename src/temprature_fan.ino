// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DH11.h"
#include "ReadTemprature.h"
#include "pwm_fan.h"
#include "myblinker.h"

const int tempSensors = 8;

float temps[tempSensors];

DH11Logic dht = DH11Logic();
void tempControl()
{
    int count = readTemprature(temps); 
    Serial.print("count: ");
    Serial.println(count);
    control(temps, count);
    for (size_t i = 0; i < count; i++)
    {
      Serial.println(temps[i]);
    }
}

void setup() {
  Serial.begin(115200);

  dht.setup();
  fanSetup();

  blinkerSetup();

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  float dt11[2];
  dht.readTempAndHumidity(dt11);

  tempControl();

  blinkerRun(dt11, temps);
  
}
