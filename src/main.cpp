#include <Adafruit_CircuitPlayground.h>
#include "RGBConverter.h"
#include "RgbLed.h"
#include "Servo.h"
#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

int currentLed = 0;
int brightness = 4;
int bri = 0;
int currentMenu = 0;
int menu = 9;
int speedwheel = 100;

RgbLed led0(0), led1(1), led2(2), led3(3), led4(4), led5(5), led6(6), led7(7), led8(8), led9(9);
RgbLed leds[10] = {led0, led1, led2, led3, led4, led5, led6, led7, led8, led9};
ThreadController controll = ThreadController();
Thread positionThread = Thread();
Thread colorThread = Thread();
Thread updateThread = Thread();
Thread sensorThread = Thread();

Thread servoThread = Thread();

#define SERVOMIN 200 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 400 // This is the 'maximum' pulse length count (out of 4096)

#define SERVO_FREQ 52 // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver();
Servo servo0(0, servoDriver);
Servo servo1(1, servoDriver);
Servo servo2(2, servoDriver);
Servo servo3(3, servoDriver);
Servo servo4(4, servoDriver);
Servo servo5(5, servoDriver);
Servo servo6(6, servoDriver);
Servo servo7(7, servoDriver);
Servo servo8(8, servoDriver);
Servo servo9(9, servoDriver);
Servo servo10(10, servoDriver);
Servo servo11(11, servoDriver);
Servo servo12(12, servoDriver);
Servo servo13(13, servoDriver);
Servo servo14(14, servoDriver);
Servo servo15(15, servoDriver);
double degree = 0.0;
void sensorThreadCallback()
{

  float x = CircuitPlayground.motionX();
  float y = CircuitPlayground.motionY();
  float z = CircuitPlayground.motionZ();
  // Serial.print(" xyz \t");
  // Serial.print(x);
  // Serial.print(" \t");
  // Serial.print(y);
  // Serial.print("\t");
  // Serial.print(z);
  // Serial.println("");
}

void colorThreadCallback()
{
  leds[currentLed].updateColor();
}
void positionThreadCallback()
{
  leds[currentLed].fadeOut();
  currentLed--;
  if (currentLed < 0)
  {
    currentLed = 9;
  }
  leds[currentLed].on();
}

void updateThreadCallback()
{
  for (int i = 9; i >= 0; i--)
  {
    leds[i].update();
  }
}
bool servoSwipeUp = true;
void servoThreadCallback()
{
  if(servoSwipeUp) {
    degree += 90.0;
  } else
  {
    degree-=90.0;
  }
  
  if (degree >= 90.0)
  {
    servoSwipeUp = false;
  }
  if (degree <= -90.0)
  {
    servoSwipeUp = true;
  }

  servo0.setPosition(degree);
  servo1.setPosition(degree);
  servo2.setPosition(degree);
  servo3.setPosition(degree);
  servo4.setPosition(degree);
  servo5.setPosition(degree);
  servo6.setPosition(degree);
  servo7.setPosition(degree);
  servo8.setPosition(degree);
  servo9.setPosition(degree);
  servo10.setPosition(degree);
  servo11.setPosition(degree);
  servo12.setPosition(degree);
  servo13.setPosition(degree);
  servo14.setPosition(degree);
  servo15.setPosition(degree);
}

void setup()
{

  CircuitPlayground.begin();
  Serial.begin(9600);

  CircuitPlayground.setBrightness(brightness);

  positionThread.onRun(positionThreadCallback);
  positionThread.setInterval(speedwheel);

  colorThread.onRun(colorThreadCallback);
  colorThread.setInterval(10);

  updateThread.onRun(updateThreadCallback);
  updateThread.setInterval(10);

  sensorThread.onRun(sensorThreadCallback);
  sensorThread.setInterval(50);

  servoThread.onRun(servoThreadCallback);
  servoThread.setInterval(1000);//270

  controll.add(&positionThread);
  controll.add(&colorThread);
  controll.add(&updateThread);
  controll.add(&sensorThread);
  controll.add(&servoThread);
  // controll.run();

  servoDriver.begin();
  servoDriver.setOscillatorFrequency(27000000);
  servoDriver.setPWMFreq(SERVO_FREQ);
}
void beepMax()
{
  CircuitPlayground.playTone(440, 50);
  delay(5);
  CircuitPlayground.playTone(440, 10);
}
void beepButton()
{
  CircuitPlayground.playTone(50, 10, 50);
}
void updateBrightness(bool up)
{
  if (up)
  {
    brightness++;
  }
  else
  {
    brightness--;
  }

  if (brightness >= 255)
  {
    beepMax();
    brightness = 255;
  }
  if (brightness <= 0)
  {
    beepMax();
    brightness = 0;
  }

  CircuitPlayground.setBrightness(brightness);
}

void updateSpeedWheel(bool up)
{

  if (up)
  {
    speedwheel++;
  }
  else
  {
    speedwheel--;
  }

  if (speedwheel >= 255)
  {
    beepMax();
    speedwheel = 255;
  }
  if (speedwheel <= 10)
  {
    beepMax();
    speedwheel = 10;
  }
  //Serial.print("speedwheel : ");
  //Serial.println(speedwheel);
  positionThread.setInterval(speedwheel);
}

void onMenuUp()
{

  beepButton();
  delay(100);
  leds[currentMenu].resetAlwaysOn();
  leds[menu].setAlwaysOn();
  currentMenu = menu;
  menu -= 1;
  Serial.print("currentMenu : ");
  Serial.print(currentMenu);
  Serial.print(" menu : ");
  Serial.println(menu);
  if (menu < 0)
  {

    Serial.println("reset menu ");
    menu = 9;
    currentMenu = 0;
    leds[currentMenu].resetAlwaysOn();
    leds[menu].resetAlwaysOn();
  }
}
void onMenuDown()
{

  beepButton();
  delay(100);
  leds[currentMenu].resetAlwaysOn();
  leds[menu].setAlwaysOn();
  currentMenu = menu;
  menu += 1;
  Serial.print("currentMenu : ");
  Serial.print(currentMenu);
  Serial.print(" menu : ");
  Serial.println(menu);
  if (menu > 9)
  {

    Serial.println("reset menu ");
    menu = 0;
    currentMenu = 9;
    leds[currentMenu].resetAlwaysOn();
    leds[menu].resetAlwaysOn();
  }
}
void updateServoMaxSample(bool up, int servoNum)
{
  if (up)
  {
    servo0.incrMaxSample();

    servo1.incrMaxSample();
    servo2.incrMaxSample();
    servo3.incrMaxSample();
    servo4.incrMaxSample();
    servo5.incrMaxSample();
    servo6.incrMaxSample();
    servo7.incrMaxSample();
    servo8.incrMaxSample();
    servo9.incrMaxSample();
    servo10.incrMaxSample();
    servo11.incrMaxSample();
    servo12.incrMaxSample();
    servo13.incrMaxSample();
    servo14.incrMaxSample();
    servo15.incrMaxSample();
  }
  else
  {
    servo0.decrMaxSample();
    servo1.decrMaxSample();
    servo2.decrMaxSample();
    servo3.decrMaxSample();
    servo4.decrMaxSample();
    servo5.decrMaxSample();
    servo6.decrMaxSample();
    servo7.decrMaxSample();
    servo8.decrMaxSample();
    servo9.decrMaxSample();
    servo10.decrMaxSample();
    servo11.decrMaxSample();
    servo12.decrMaxSample();
    servo13.decrMaxSample();
    servo14.decrMaxSample();
    servo15.decrMaxSample();
  }
}
void updateServoMinSample(bool up, int servoNum)
{
  if (up)
  {
    servo0.incrMinSample();
    servo1.incrMinSample();
    servo2.incrMinSample();
    servo3.incrMinSample();
    servo4.incrMinSample();
    servo5.incrMinSample();
    servo6.incrMinSample();
    servo7.incrMinSample();
    servo8.incrMinSample();
    servo9.incrMinSample();
    servo10.incrMinSample();
    servo11.incrMinSample();
    servo12.incrMinSample();
    servo13.incrMinSample();
    servo14.incrMinSample();
    servo15.incrMinSample();
  }
  else
  {
    servo0.decrMinSample();
    servo1.decrMinSample();
    servo2.decrMinSample();
    servo3.decrMinSample();
    servo4.decrMinSample();
    servo5.decrMinSample();
    servo6.decrMinSample();
    servo7.decrMinSample();
    servo8.decrMinSample();
    servo9.decrMinSample();
    servo10.decrMinSample();
    servo11.decrMinSample();
    servo12.decrMinSample();
    servo13.decrMinSample();
    servo14.decrMinSample();
    servo15.decrMinSample();
  }
}
void setSubMenu(bool up)
{
  if (currentMenu == 9)
  {
    updateBrightness(up);
  }
  if (currentMenu == 8)
  {
    updateSpeedWheel(up);
  }
  if (currentMenu == 7)
  {
    updateServoMaxSample(up, 0);
  }
  if (currentMenu == 6)
  {
    updateServoMinSample(up, 0);
  }
  if (currentMenu == 4)
  {
  }
  if (currentMenu == 3)
  {
  }
  if (currentMenu == 2)
  {
  }
  if (currentMenu == 0)
  {
  }
  if (currentMenu == 0)
  {
  }
}
void onLeftButtonClick()
{
  delay(10);
  beepButton();
  setSubMenu(false);
}
void onRightButtonClick()
{
  delay(10);
  beepButton();
  setSubMenu(true);
}
void onCapa10()
{
  delay(50);
  onMenuDown();
}
void onCapa9()
{
  delay(50);
  onMenuUp();
}

void loop()
{
  controll.run();

  boolean rightButton = CircuitPlayground.rightButton();
  if (rightButton == true)
  {
    onRightButtonClick();
  }

  boolean leftButton = CircuitPlayground.leftButton();
  if (leftButton == true)
  {
    onLeftButtonClick();
  }

  uint16_t capa10 = CircuitPlayground.readCap(10, 10);
  if (capa10 > 30)
  {
    onCapa10();
  }

  uint16_t capa9 = CircuitPlayground.readCap(9, 10);
  if (capa9 > 30)
  {
    onCapa9();
  }

  uint16_t capa6 = CircuitPlayground.readCap(6, 10);
  if (capa6 > 30)
  {

    float x = CircuitPlayground.motionX();
    float y = CircuitPlayground.motionY();
    long mapped = abs(map(long(y * 1000), -10000, 10000, 1, 50));
    Serial.println(mapped);
    CircuitPlayground.playTone(map(long(x * 100), -1000, 1000, 100, 4000), mapped, 5);
  }
  uint16_t capa12 = CircuitPlayground.readCap(12, 10);

  if (capa12 > 30)
  {
    for (int i = 0; i < map(rand(), 0, RAND_MAX, 7, 30); i++)
      CircuitPlayground.playTone(map(rand(), 0, RAND_MAX, 100, 3000), map(rand(), 0, RAND_MAX, 1, 200), map(rand(), 0, RAND_MAX, 1, 1000));
  }
}