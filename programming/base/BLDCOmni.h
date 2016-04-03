#ifndef BLDCOMNI_H
#define BLDCOMNI_H
#include<Arduino.h>
#include"MyMotor.h"

class BLDCOmni {
  private:
    int speedPin;
    int brakePin;

    MyMotor m1;
    MyMotor m2;
    MyMotor m3;
    MyMotor m4;

  public:
    BLDCOmni(int _speedPin, int _brakePin);
    void setMag(int mag);
    void setDir(byte dir);
    void brake();
    void rotate(char d, int m);

    void setMotor1(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor);
    void setMotor2(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor);
    void setMotor3(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor);
    void setMotor4(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor);

    int getRPM(int motor);
};
#endif

