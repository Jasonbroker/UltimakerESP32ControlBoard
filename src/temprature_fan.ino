// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DH11.h"
#include "ReadTemprature.h"
#include "PWMFanController.h"
#include "myblinker.h"

const int tempSensors = 8;

float temps[tempSensors];

DH11Logic dht = DH11Logic();
PWMFanController fanController = PWMFanController();

void setup() {
  Serial.begin(115200);

  dht.setup();
  fanController.setup();

  blinkerSetup();

}

float dt11[2];
void loop() {

  dht.readTempAndHumidity(dt11);
  // 获取温度列表
  int count = readTemprature(temps); 
  // 
  fanController.control(temps, count);

  blinkerRun(dt11, temps);
  
}