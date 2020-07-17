#include <Adafruit_PWMServoDriver.h>
class Servo
{

private:
    int _id;
    double _degreePosition = 0.0;
    double _max = 90.0;
    double _min = -90.0;
    double _ofset = 0;
    Adafruit_PWMServoDriver _driver;
    double _minSample = 99;//85.0;
    double _maxSample = 412;//443.0;

public:
    Servo(int id, Adafruit_PWMServoDriver driver);
    void setPosition(double degree);
    void setMax(double degree);
    void setMin(double degree);

    void setMaxSample(double degree);
    void setMinSample(double degree);
    void incrMaxSample();
    void decrMaxSample();
    void incrMax();
    void decrMax();

    void incrMinSample();
    void decrMinSample();
    void incrMin();
    void decrMin();
};