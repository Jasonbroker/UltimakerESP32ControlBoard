// the number of the LED pin
#include "PWMFan.h"
#include "Pins.h"
#include "Configration.h"

void PWMFan::changeSpeedForTemp(float temp)
{
    if (temp > 35) {
        ledcWrite(_channel, 255);  // 输出PWM
    } else if (temp > 33) {
        ledcWrite(_channel, 210);  // 输出PWM
    } else if (temp > 30) {
        ledcWrite(_channel, 150);  // 输出PWM
    } else {
        ledcWrite(_channel, 0);  // 输出PWM
    }
    Serial.print("PWMFan controling channel: ");
    Serial.println(_channel);
    Serial.print(" at temp:");
    Serial.print(temp);
}