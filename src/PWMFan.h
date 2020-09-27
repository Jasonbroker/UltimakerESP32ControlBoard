class PWMFan 
{
public:
    void setup();
    void control(float temps[], int count);
private:
    void changeSpeedForTemp(float temp, int channel);
};