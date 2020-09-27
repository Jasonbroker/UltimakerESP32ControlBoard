#ifdef ENABLE_BLINK
#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <Blinker.h>
#include "Pins.h"

char auth[] = "70e5abcc82b5";
char ssid[] = "Danke502";
char pswd[] = "wifi.danke.life";

// 新建组件对象
BlinkerButton Button1("btn-abc");
BlinkerNumber Number1("num-abc");

BlinkerNumber HUMI("humi");
BlinkerNumber TEMP("temp");
BlinkerNumber TEMP1("temp1");
BlinkerNumber TEMP2("temp2");
BlinkerNumber TEMP3("temp3");
BlinkerNumber TEMP4("temp4");

float humi_read = 0, temp_read = 0;
float tempx, tempy, tempz, tempe = 0;
#endif

void heartbeat()
{
#ifdef ENABLE_BLINK
    HUMI.print(humi_read);
    TEMP.print(temp_read);
    TEMP1.print(tempx);
    TEMP2.print(tempy);
    TEMP3.print(tempz);
    TEMP4.print(tempe);
#endif
}

void dataStorage()
{
#ifdef ENABLE_BLINK
    Blinker.dataStorage("temp", temp_read);
    Blinker.dataStorage("humi", humi_read);
#endif
}

int counter = 0;

#define LED_BUILTIN 2

// 按下按键即会执行该函数
#ifdef ENABLE_BLINK
void button1_callback(const String & state) {

    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
#endif

// 如果未绑定的组件被触发，则会执行其中内容
#ifdef ENABLE_BLINK
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}
#endif

// #define ENABLE_BLINK

void blinkerSetup() {
    // 初始化串口
#ifdef ENABLE_BLINK
    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif

    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachHeartbeat(heartbeat);
    Blinker.attachDataStorage(dataStorage);
    Button1.attach(button1_callback);

    Blinker.attachData(dataRead);
#endif
}

void blinkerRun(float dht11[], float temps[])
{
#ifdef ENABLE_BLINK
    Blinker.run();

    humi_read = dht11[0];
    temp_read = dht11[1];

    tempx = temps[0];
    tempy = temps[1];
    tempz = temps[2];
    tempe = temps[3];

    Blinker.delay(2000);
#endif
}
