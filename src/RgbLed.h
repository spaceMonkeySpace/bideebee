
#include "RGBConverter.h"
class RgbLed
{

private:
    byte _rgb[3];
    int _pinNumber;
    unsigned long _timeoutHue;
    double _hue = 0.3;
    double _saturation = 1;
    double _maxBrightness = 0.2;
    double _lighting = _maxBrightness;
    boolean _isFadout;
    boolean _upcolor = true;
    boolean _isAlwaysOn;
    RGBConverter converter;


public:
    void updateFadeOut();
    RgbLed(int pinNumber);
    void update();
    void updateColor();
    void fadeOut();
    void on();
    void setMaxBrightness(double value);
    void setAlwaysOn();
    void resetAlwaysOn();
    
};