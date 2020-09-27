// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DH11.h"
#include "ReadTemprature.h"
#include "PWMFanController.h"
#include "myblinker.h"
#include "Configration.h"
#include "SerialConnection/UltiSerial.h"

float temps[NUM_TEMP_SENSORS];

DH11Logic dht = DH11Logic();
PWMFanController fanController = PWMFanController();
UltiSerial ultiSerial = UltiSerial();

void setup() {
  Serial.begin(115200);

  dht.setup();
  
  blinkerSetup();

  ultiSerial.begin();

}

void loop() {

  float temp = dht.readHumidity();
  float humidty = dht.readHumidity();
  // 获取温度列表
  int count = readTemprature(temps); 
  // 
  fanController.control(temps, count);

  ultiSerial.work();

  // blinkerRun(dt11, temps);
  
}