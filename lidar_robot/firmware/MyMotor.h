#ifndef _MY_MOTOR_
#define _MY_MOTOR_

#include<Arduino.h>

class MyMotor {
  private:
    int disablePin;
    int directionPin;
    int speedPin;
    int brakePin;
    float correctionFactor;

  public:
    void init (int _speedPin, int _disablePin, int _directionPin, int _brakePin, float _correctionFactor);
    void acw();
    void cw();
    void off();
    void setMag(int _mag);
    void brakeOn();
    void brakeOff();
};

#endif
