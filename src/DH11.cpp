#include "Pins.h"
#include "DH11.h"
#include "Configration.h"
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!

//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.



void DH11Logic::setup()
{
    _lastTempTime = _lastHumiTime = 0;
    _dht.begin();
}

float DH11Logic::readHumidity()
{
    float ts = millis();
    
    if (_lastHumiTime &&
     (ts - _lastHumiTime < DH11_READ_INTERVAL))
    {
        return _cachedHumidity;
    }
    float h = _dht.readHumidity();
    _lastHumiTime = ts;
    if (isnan(h)) {
        Serial.println("Failed to read from DHT sensor!");
        return -1;
    }
    Serial.print("Read humi ");
    Serial.print(h);
    Serial.println("%");
    _cachedHumidity = h;
    return h;
}

float DH11Logic::readTemperature()
{
  float ts = millis();
    if (_lastTempTime &&
     (ts - _lastTempTime < DH11_READ_INTERVAL))
    {
        return _cachedTemp;
    }
    float t = _dht.readTemperature();

    _lastTempTime = ts;
    if (isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return -1;
    }
    Serial.print("Read temp ");
    Serial.print(t);
    Serial.println("°C");
    _cachedTemp = t;
    return t;
}