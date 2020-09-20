#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <Blinker.h>

char auth[] = "70e5abcc82b5";
char ssid[] = "Danke502";
char pswd[] = "wifi.danke.life";

// 新建组件对象
BlinkerButton Button1("btn-abc");
BlinkerNumber Number1("num-abc");

BlinkerNumber HUMI("humi");
BlinkerNumber TEMP("temp");

float humi_read = 0, temp_read = 0;

void heartbeat()
{
    HUMI.print(humi_read);
    TEMP.print(temp_read);
}

void dataStorage()
{
    Blinker.dataStorage("temp", temp_read);
    Blinker.dataStorage("humi", humi_read);
}

int counter = 0;

#define LED_BUILTIN 2

// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}

#define ENABLE_BLINK

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

void blinkerRun(float dh11[]) {
#ifdef ENABLE_BLINK
    Blinker.run();

    humi_read = dh11[0];
    temp_read = dh11[1];

    Blinker.delay(2000);
#endif
}