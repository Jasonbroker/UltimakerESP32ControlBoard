// the number of the LED pin
#include <Arduino.h>

const int ledPin = 4; // 16 corresponds to GPIO16

// setting PWM properties

const int freq = 100;

const int ledChannel = 0;

const int resolution = 8;

int relayPin1 = 22; //继电器引脚
int relayPin2 = 23; //继电器引脚

void fanSetup(){

    // configure LED PWM functionalitites

    ledcSetup(ledChannel, freq, resolution);

// attach the channel to the GPIO to be controlled

    ledcAttachPin(ledPin, ledChannel);

    pinMode(relayPin1, OUTPUT);
    pinMode(relayPin2, OUTPUT);

}

void control(float temps[], int count)
{
    // if (threhold > 40) {
    //     ledcWrite(ledChannel, 255);  // 输出PWM
    // } else if (threhold > 35) {
    //     ledcWrite(ledChannel, 200);  // 输出PWM
    // } else if (threhold > 30 ) {
    //     ledcWrite(ledChannel, 150);  // 输出PWM
    // } else {
    //     ledcWrite(ledChannel, 0);  // 输出PWM
    // }
    if (count < 4)
    {
        digitalWrite(relayPin1, HIGH);
        digitalWrite(relayPin2, HIGH);
        return;
    }    
    if (count == 4)
    {
        Serial.print("结果：");
        Serial.print(temps[2]);
        Serial.println(temps[2] > 33);
        int num = digitalRead(relayPin1);
        Serial.println(num);
        Serial.println(digitalRead(relayPin2));

        // digitalWrite(relayPin1, temps[2] > 33 ? HIGH : LOW);
        // digitalWrite(relayPin2, temps[3] > 33 ? HIGH : LOW);
        digitalWrite(relayPin1, HIGH);
        digitalWrite(relayPin2, HIGH);        
    }
}
