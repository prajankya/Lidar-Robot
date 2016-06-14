#include<Arduino.h>
#include"MyMotor.h"


void MyMotor::init(int _speedPin, int _disablePin, int _directionPin, int _brakePin, float _correctionFactor) {
  speedPin = _speedPin;
  disablePin = _disablePin;
  directionPin = _directionPin;
  brakePin = _brakePin;
  correctionFactor = _correctionFactor;

  pinMode(disablePin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(brakePin, OUTPUT);
}

void MyMotor::acw() {
  digitalWrite(directionPin, LOW);
  digitalWrite(disablePin, HIGH);
}

void MyMotor::cw() {
  digitalWrite(directionPin, HIGH);
  digitalWrite(disablePin, HIGH);
}

void MyMotor::off() {
  digitalWrite(disablePin, LOW);
}

void MyMotor::setMag(int _mag) {
  analogWrite(speedPin, constrain(round(correctionFactor * _mag), 0, 255));
}

void MyMotor::brakeOn() {
  digitalWrite(brakePin, HIGH);
}
void MyMotor::brakeOff() {
  digitalWrite(brakePin, LOW);
}

