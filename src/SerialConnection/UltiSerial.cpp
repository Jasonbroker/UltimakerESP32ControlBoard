#include "UltiSerial.h"
#include <HardwareSerial.h>

void UltiSerial::begin()
{
    Serial2.begin(9600, SERIAL_8N1, 19, 22);
}

void UltiSerial::work()
{
    while (Serial2.available() > 0) {
        String byteFromSerial = Serial2.readStringUntil('\n');
        Serial.print(byteFromSerial);
    }
}