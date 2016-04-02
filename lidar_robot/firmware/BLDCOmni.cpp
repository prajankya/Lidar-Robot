#include<Arduino.h>
#include"BLDCOmni.h"
#include"MyMotor.h"

BLDCOmni::BLDCOmni(int _speedPin, int _brakePin) {
  speedPin = _speedPin;
  brakePin = _brakePin;
  pinMode(brakePin, OUTPUT);
}

void BLDCOmni::init(){
  digitalWrite(brakePin, HIGH);
  analogWrite(speedPin, 0);
}

void BLDCOmni::setMag(int mag) {
  analogWrite(speedPin, constrain(mag, 0, 30));
}

void BLDCOmni::brakeOn() {
  digitalWrite(brakePin, HIGH);
}

void BLDCOmni::brakeOff(){
  digitalWrite(brakePin, LOW);
}

String BLDCOmni::getDir(){
 return curDir;
}

void BLDCOmni::setDir(byte dir) {
  switch (dir) {
    case 8:
      curDir="UP";
      m1.cw();
      m2.off();
      m3.acw();
      m4.off();
      break;
    case 2:
      curDir="Down";
      m1.acw();
      m2.off();
      m3.cw();
      m4.off();
      break;
    case 4:
      curDir= "Left";
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
