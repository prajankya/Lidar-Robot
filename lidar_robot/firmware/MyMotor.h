#ifndef _MY_MOTOR_
#define _MY_MOTOR_

#include<Arduino.h>

class MyMotor {
  private:
    int disablePin;
    int directionPin;
    int tachoPin;
    float correctionFactor;

  public:

    void init (int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor);
    void acw();
    void cw();
    void off();
    int rpm();
};

#endif
