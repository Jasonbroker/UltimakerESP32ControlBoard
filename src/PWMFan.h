
class PWMFan 
{
public:
    void setup();
    void control(float temps[], int count);
private:
    const int freq = 40;
    const int resolution = 8;
    void changeSpeedForTemp(float temp, int channel);
};