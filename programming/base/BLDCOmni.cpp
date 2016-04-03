#include<Arduino.h>
#include"BLDCOmni.h"

BLDCOmni::BLDCOmni(int _speedPin, int _brakePin) {
  speedPin = _speedPin;
  brakePin = _brakePin;
  pinMode(speedPin, OUTPUT);
  pinMode(brakePin, OUTPUT);
}

void BLDCOmni::setMag(int mag) {
  analogWrite(speedPin, mag);
  Serial.println(mag);
}
void BLDCOmni::brake(){
  digitalWrite(brakePin,HIGH);
  setMag(0);
  setDir(5);
  digitalWrite(brakePin,LOW);
}

void BLDCOmni::rotate(char d,int m){
  if(d=='l'){
    m1.acw();
    m2.acw();
    m3.acw();
    m4.acw();
  }
  else if(d=='r'){
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

void BLDCOmni::setMotor1(int _disablePin, int _directionPin, int _tachoPin) {
  m1.init(_disablePin, _directionPin, _tachoPin);
}

void BLDCOmni::setMotor2(int _disablePin, int _directionPin, int _tachoPin) {
  m2.init(_disablePin, _directionPin, _tachoPin);
}

void BLDCOmni::setMotor3(int _disablePin, int _directionPin, int _tachoPin) {
  m3.init(_disablePin, _directionPin, _tachoPin);
}

void BLDCOmni::setMotor4(int _disablePin, int _directionPin, int _tachoPin) {
  m4.init(_disablePin, _directionPin, _tachoPin);
}

void MyMotor::init(int _disablePin, int _directionPin, int _tachoPin) {
  disablePin = _disablePin;
  directionPin = _directionPin;
  tachoPin = _tachoPin;

  pinMode(disablePin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(tachoPin, INPUT);
}

void MyMotor::acw(){
  digitalWrite(directionPin, LOW);
  digitalWrite(disablePin, HIGH);
}

void MyMotor::cw(){
  digitalWrite(directionPin, HIGH);
  digitalWrite(disablePin, HIGH);
}

void MyMotor::off(){
  digitalWrite(disablePin, LOW);
}
