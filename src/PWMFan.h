#include <Arduino.h>

class PWMFan {
private:
    int8_t _channel;
public:
    PWMFan(int8_t channel, int32_t frequency, int8_t resolution, int8_t pin) {
        ledcSetup(channel, frequency, resolution);
        ledcAttachPin(pin, channel);
        _channel = channel;
    };
    void changeSpeedForTemp(float temp);
};