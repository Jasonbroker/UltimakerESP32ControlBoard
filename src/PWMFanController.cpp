#include "PWMFanController.h"

void PWMFanController::control(float temps[], int count)
{
    if (count > 1)
    {
        float tempx = temps[X_AXIS];
        _xFan.changeSpeedForTemp(tempx);

        float tempy = temps[Y_AXIS];
        _yFan.changeSpeedForTemp(tempy);

        float tempz = temps[Z_AXIS] + 1;
        _boardFan.changeSpeedForTemp(tempz);
    
    }
}