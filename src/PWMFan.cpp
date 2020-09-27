// the number of the LED pin
#include "PWMFan.h"
#include <Arduino.h>
#include "Pins.h"
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define E_AXIS 3

#define X_AXIS_CHANNEL X_AXIS
#define Y_AXIS_CHANNEL Y_AXIS
#define Z_AXIS_CHANNEL Z_AXIS
#define E_AXIS_CHANNEL E_AXIS


void PWMFan::setup()
{

    // configure LED PWM functionalitites
    ledcSetup(X_AXIS_CHANNEL, this->freq, this->resolution);
    ledcSetup(Y_AXIS_CHANNEL, this->freq, this->resolution);
    ledcSetup(Z_AXIS_CHANNEL, this->freq, this->resolution);

// attach the channel to the GPIO to be controlled

    ledcAttachPin(AXIS_X_PIN, X_AXIS);
    ledcAttachPin(AXIS_Y_PIN, Y_AXIS);
    ledcAttachPin(AXIS_Z_PIN, Z_AXIS);

}

void PWMFan::changeSpeedForTemp(float temp, int channel)
{
    if (temp > 35) {
        ledcWrite(channel, 255);  // 输出PWM
    } else if (temp > 33) {
        ledcWrite(channel, 210);  // 输出PWM
    } else if (temp > 30) {
        ledcWrite(channel, 150);  // 输出PWM
    } else {
        ledcWrite(channel, 0);  // 输出PWM
    }
    Serial.print("controling temp threahold");
    Serial.println(temp);
}

void PWMFan::control(float temps[], int count)
{
    if (count > 1)
    {
    float tempx = temps[X_AXIS];
    changeSpeedForTemp(tempx, X_AXIS_CHANNEL);

    float tempy = temps[Y_AXIS];
    changeSpeedForTemp(tempy, Y_AXIS_CHANNEL);

    float tempz = temps[Z_AXIS] + 1;
    changeSpeedForTemp(tempz, Z_AXIS_CHANNEL);
    
    }
}
