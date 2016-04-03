#include<Arduino.h>
#include"BLDCOmni.h"
#include"MyMotor.h"

BLDCOmni::BLDCOmni(int _speedPin, int _brakePin) {
  speedPin = _speedPin;
  brakePin = _brakePin;
  pinMode(speedPin, OUTPUT);
  pinMode(brakePin, OUTPUT);
}

void BLDCOmni::setMag(int mag) {
  analogWrite(speedPin, constrain(mag, 0, 30));
}

void BLDCOmni::brake() {
  digitalWrite(brakePin, HIGH);
  setMag(0);
  setDir(5);
  digitalWrite(brakePin, LOW);
}

void BLDCOmni::rotate(char d, int m) {
  if (d == 'l') {
    m1.acw();
    m2.acw();
    m3.acw();
    m4.acw();
  }
  else if (d == 'r') {
    m1.cw();
    m2.cw();
    m3.cw();
    m4.cw();
  }
  setMag(m);
}

void BLDCOmni::setDir(byte dir) {
  switch (dir) {
    case 1:
      m1.acw();
      m2.off();
      m3.cw();
      m4.off();
      break;
    case 2:
      m1.acw();
      m2.acw();
      m3.cw();
      m4.cw();
      break;
    case 3:
      m1.off();
      m2.acw();
      m3.off();
      m4.cw();
      break;
    case 4:
      m1.acw();
      m2.cw();
      m3.cw();
      m4.acw();
      break;
    case 5:
      m1.off();
      m2.off();
      m3.off();
      m4.off();
      break;
    case 6:
      m1.cw();
      m2.acw();
      m3.acw();
      m4.cw();
      break;
    case 7:
      m1.off();
      m2.cw();
      m3.off();
      m4.acw();
      break;
    case 8:
      m1.cw();
      m2.cw();
      m3.acw();
      m4.acw();
      break;
    case 9:
      m1.cw();
      m2.off();
      m3.acw();
      m4.off();
      break;
    default:
      setDir(5);
      break;
  }
}

int BLDCOmni::getRPM(int motor) {
  switch (motor) {
    case 1:
      return m1.rpm();
      break;
    case 2:
      return m2.rpm();
      break;
    case 3:
      return m3.rpm();
      break;
    case 4:
      return m4.rpm();
      break;
    default:
      return 0;
  }
}

void BLDCOmni::setMotor1(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor) {
  m1.init(_disablePin, _directionPin, _tachoPin, _correctionFactor);
}

void BLDCOmni::setMotor2(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor) {
  m2.init(_disablePin, _directionPin, _tachoPin, _correctionFactor);
}

void BLDCOmni::setMotor3(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor) {
  m3.init(_disablePin, _directionPin, _tachoPin, _correctionFactor);
}

void BLDCOmni::setMotor4(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor) {
  m4.init(_disablePin, _directionPin, _tachoPin, _correctionFactor);
}
