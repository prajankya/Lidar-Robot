#include<Arduino.h>
#include"BLDCOmni.h"
#include"MyMotor.h"

void BLDCOmni::setMag(int mag) {
  m1.setMag(mag);
  m2.setMag(mag);
  m3.setMag(mag);
  m4.setMag(mag);
}

void BLDCOmni::brakeOn() {
  m1.brakeOn();
  m2.brakeOn();
  m3.brakeOn();
  m4.brakeOn();
}

void BLDCOmni::brakeOff() {
  m1.brakeOff();
  m2.brakeOff();
  m3.brakeOff();
  m4.brakeOff();
}

String BLDCOmni::getDir() {
  return curDir;
}

void BLDCOmni::setDir(byte dir) {
  switch (dir) {
    case 8:
      curDir = "UP";
      m1.cw();
      m2.off();
      m3.acw();
      m4.off();
      break;
    case 2:
      curDir = "Down";
      m1.acw();
      m2.off();
      m3.cw();
      m4.off();
      break;
    case 4:
      curDir = "Left";
      m1.off();
      m2.cw();
      m3.off();
      m4.acw();
      break;
    case 6:
      curDir = "Right";
      m1.off();
      m2.acw();
      m3.off();
      m4.cw();
      break;
    case 9:
      curDir = "Top-Right";
      m1.cw();
      m2.acw();
      m3.acw();
      m4.cw();
      break;
    case 7:
      curDir = "Top-Left";
      m1.cw();
      m2.cw();
      m3.acw();
      m4.acw();
      break;
    case 1:
      curDir = "Bottom-left";
      m1.acw();
      m2.cw();
      m3.cw();
      m4.acw();
      break;
    case 3:
      curDir = "Bottom-Right";
      m1.acw();
      m2.acw();
      m3.cw();
      m4.cw();
      break;
    case 5:
      curDir = "Stop";
      m1.off();
      m2.off();
      m3.off();
      m4.off();
      break;
    /*    case '+':
          m1.cw();
          m2.cw();
          m3.cw();
          m4.cw();
          break;
        case '-':
          m1.acw();
          m2.acw();
          m3.acw();
          m4.acw();
          break;
  */    default:
      setDir(5);
      break;
  }
}

void BLDCOmni::setMotor1(int _speedPin, int _disablePin, int _directionPin, int _brakePin, float _correctionFactor) {
  m1.init(_speedPin, _disablePin, _directionPin, _brakePin, _correctionFactor);
}

void BLDCOmni::setMotor2(int _speedPin, int _disablePin, int _directionPin, int _brakePin, float _correctionFactor) {
  m2.init(_speedPin, _disablePin, _directionPin, _brakePin, _correctionFactor);
}

void BLDCOmni::setMotor3(int _speedPin, int _disablePin, int _directionPin, int _brakePin, float _correctionFactor) {
  m3.init(_speedPin, _disablePin, _directionPin, _brakePin, _correctionFactor);
}

void BLDCOmni::setMotor4(int _speedPin, int _disablePin, int _directionPin, int _brakePin, float _correctionFactor) {
  m4.init(_speedPin, _disablePin, _directionPin, _brakePin, _correctionFactor);
}
