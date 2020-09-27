#include "PWMFan.h"
#include "Configration.h"
#include "Pins.h"

class PWMFanController
{
private:
    PWMFan _xFan;
    PWMFan _yFan;
    PWMFan _boardFan;
public:

    PWMFanController():_xFan(X_AXIS_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION, X_AXIS_PIN),
    _yFan(Y_AXIS_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION, Y_AXIS_PIN),
    _boardFan(Z_AXIS_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION, BOARD_PIN)
    {}
    void control(float temps[], int count);
};