#include <RgbLed.h>
#include <Adafruit_CircuitPlayground.h>

RgbLed::RgbLed(int pinNumber)
{
    _pinNumber = pinNumber;
}
void RgbLed::updateFadeOut()
{
    if (_isFadout && _lighting >= 0)
    {
        _lighting -= 0.01;

        if (_lighting <= 0)
        {
            _lighting = 0;
        }
    }
}
void RgbLed::on()
{
    _isFadout = false;
    _lighting += 0.2;

    if (_lighting >= _maxBrightness)
    {
        _lighting = _maxBrightness;
    }
    _lighting = _maxBrightness;
}
void RgbLed::setMaxBrightness(double value)
{
    _maxBrightness = value;
}
void RgbLed::fadeOut()
{
    _isFadout = true;
}
void RgbLed::updateColor()
{
    if (_upcolor == true)
    {
        _hue += 0.01;
    }
    else
    {
        _hue -= 0.01;
    }
    if (_hue >= 1)
    {
        _upcolor = false;
    }
    if (_hue <= 0)
    {
        _upcolor = true;
    }

    //   Serial.print(" rgb (");
    // Serial.print(_rgb[0]);
    // Serial.print(" ,");
    // Serial.print(_rgb[1]);
    // Serial.print(",");
    // Serial.print(_rgb[2]);
    // Serial.println(")");
}
void RgbLed::setAlwaysOn()
{
    _isAlwaysOn = true;
    CircuitPlayground.setPixelColor(_pinNumber, 0, 50, 255);
}
void RgbLed::resetAlwaysOn()
{
    _isAlwaysOn = false;
}

void RgbLed::update()
{
    if (_isAlwaysOn == false)
    {
        updateFadeOut();

        converter.hslToRgb(_hue, _saturation, _lighting, _rgb);
        CircuitPlayground.setPixelColor(_pinNumber, _rgb[0], _rgb[1], _rgb[2]);
    }
}