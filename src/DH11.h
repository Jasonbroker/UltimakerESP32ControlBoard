
#include <DHT.h>
#include "Pins.h"

class DH11Logic
{
private:
    DHT _dht;
    float _lastTempTime;
    float _lastHumiTime;
    float _cachedTemp;
    float _cachedHumidity;
public:
    DH11Logic():_dht(DHTPIN, DHTTYPE){};
    void setup();
    float readTemperature();
    float readHumidity();
};




