#ifndef BLDCOMNI_H
#define BLDCOMNI_H
#include<Arduino.h>

class MyMotor {
private:
  int disablePin;
  int directionPin;
  int tachoPin;
public:

  void init (int _disablePin, int _directionPin, int _tachoPin);
  void acw();
  void cw();
  void off();
};


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
  void rotate(char d,int m);

  void setMotor1(int _disablePin, int _directionPin, int _tachoPin);
  void setMotor2(int _disablePin, int _directionPin, int _tachoPin);
  void setMotor3(int _disablePin, int _directionPin, int _tachoPin);
  void setMotor4(int _disablePin, int _directionPin, int _tachoPin);
};
#endif

