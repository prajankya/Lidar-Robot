#include<Arduino.h>
#include"MyMotor.h"

void MyMotor::init(int _disablePin, int _directionPin, int _tachoPin, float _correctionFactor) {
  disablePin = _disablePin;
  directionPin = _directionPin;
  tachoPin = _tachoPin;
  correctionFactor = _correctionFactor;

  pinMode(disablePin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(tachoPin, INPUT);
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

int MyMotor::rpm() {
  long high_time = pulseIn(tachoPin, HIGH, 300000);
  return floor(correctionFactor * (1000000 / high_time));
  /*

    if (high_time > 0) {
    long low_time = pulseIn(tachoPin, LOW, 300000);
    if (low_time > 0) {
      return floor(correctionFactor * constrain(map(floor(1000000 / (high_time + low_time)), 0, 100, 0, 255), 0, 255));
    }

    }*/
  //  return 0;
}

