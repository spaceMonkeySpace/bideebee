#include "Servo.h"
Servo::Servo(int id, Adafruit_PWMServoDriver driver)
{
    _driver = driver;
    if (id > 15)
    {
        id = 15;
    }
    if (id < 0)
    {
        id = 0;
    }
    _id = id;
}
double mapDouble(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x-in_min)  * ((out_max - out_min) / (in_max - in_min)) + out_min;
}
void Servo::setPosition(double degree)
{
    if (degree >= _max)
    {
        degree = _max;
    }
    if (degree <= _min)
    {
        degree = _min;
    }
    uint16_t pulse = round(mapDouble(degree, _min, _max, _minSample, _maxSample));


    Serial.print("_minSample : ");
    Serial.print(_minSample);
    Serial.print("\t_maxSample : ");
    Serial.print(_maxSample);

    Serial.print("\tdegre : ");
    Serial.print(degree);

    Serial.print("\tpulse : ");
    Serial.println(pulse);
    _driver.setPWM(_id, 0, pulse);
}
void Servo::setMax(double degree)
{
    _max = degree;
}
void Servo::setMin(double degree)
{
    _min = degree;
}

void Servo::setMinSample(double minSample)
{
    _minSample = minSample;
}
void Servo::setMaxSample(double maxSample)
{
    _maxSample = maxSample;
}

void Servo::incrMaxSample() { _maxSample++; }
void Servo::decrMaxSample() { _maxSample--; }
void Servo::incrMax() { _max++; }
void Servo::decrMax() { _max--; }
void Servo::incrMinSample() { _minSample++; }
void Servo::decrMinSample() { _minSample--; }
void Servo::incrMin() { _min++; }
void Servo::decrMin() { _min--; }