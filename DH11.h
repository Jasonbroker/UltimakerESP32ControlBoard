
#include <DHT.h>
#include "Pins.h"

class DH11Logic
{
private:
    DHT _dht;
public:
    DH11Logic():_dht(DHTPIN, DHTTYPE){};
    void readTempAndHumidity(float dt11[]);
    void setup();

};




