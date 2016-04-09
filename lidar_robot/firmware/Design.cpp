#include<Arduino.h>
#include "Design.h"

void Design::init(int _l1Pin, int _l2Pin, int _l3Pin, int _l4Pin, int _l5Pin, int _l6Pin) {
  l1Pin = _l1Pin;
  l2Pin = _l2Pin;
  l3Pin = _l3Pin;
  l4Pin = _l4Pin;
  l5Pin = _l5Pin;
  l6Pin = _l6Pin;

  /* pinMode(l1Pin, OUTPUT);
    pinMode(l2Pin, OUTPUT);
    pinMode(l3Pin, OUTPUT);
    pinMode(l4Pin, OUTPUT);
    pinMode(l5Pin, OUTPUT);
    pinMode(l6Pin, OUTPUT);

    digitalWrite(l1Pin, LOW);
    digitalWrite(l2Pin, LOW);
    digitalWrite(l3Pin, LOW);
    digitalWrite(l4Pin, LOW);
    digitalWrite(l5Pin, LOW);
    digitalWrite(l6Pin, LOW);*/

  analogWrite(l1Pin, 0);
  analogWrite(l2Pin, 0);
  analogWrite(l3Pin, 0);
  analogWrite(l4Pin, 0);
  analogWrite(l5Pin, 0);
  analogWrite(l6Pin, 0);
}

void Design::inOut(int inDelay) {
  for (int i = 0; i < 100; i++) {
    analogWrite(l1Pin, i);
    delay(inDelay);
  }
  for (int i = 100; i < 255; i++) {
    analogWrite(l1Pin, i);
    analogWrite(l2Pin, i - 100);
    delay(inDelay);
  }
  for (int i = 155; i < 255; i++) {
    analogWrite(l2Pin, i);
    analogWrite(l3Pin, i - 100);
    delay(inDelay);
  }
  for (int i = 155; i < 255; i++) {
    analogWrite(l3Pin, i);
    analogWrite(l4Pin, i - 100);
    delay(inDelay);
  }
  for (int i = 155; i < 255; i++) {
    analogWrite(l5Pin, i);
    analogWrite(l6Pin, i - 100);
    delay(inDelay);
  }
  for (int i = 155; i < 255; i++) {
    analogWrite(l6Pin, i);
    delay(inDelay);
  }
}
void Design::on() {
  analogWrite(l1Pin, 255);
  analogWrite(l2Pin, 255);
  analogWrite(l3Pin, 255);
  analogWrite(l4Pin, 255);
  analogWrite(l5Pin, 255);
  analogWrite(l6Pin, 255);
}

void Design::on(int line) {
  switch (line) {
    case 1:
      analogWrite(l1Pin, 255);
      break;
    case 2:
      analogWrite(l2Pin, 255);
      break;
    case 3:
      analogWrite(l3Pin, 255);
      break;
    case 4:
      analogWrite(l4Pin, 255);
      break;
    case 5:
      analogWrite(l5Pin, 255);
      break;
    case 6:
      analogWrite(l6Pin, 255);
      break;
    default:
      break;
  }
}

void Design::off() {
  analogWrite(l1Pin, 0);
  analogWrite(l2Pin, 0);
  analogWrite(l3Pin, 0);
  analogWrite(l4Pin, 0);
  analogWrite(l5Pin, 0);
  analogWrite(l6Pin, 0);
}

void Design::off(int line) {
  switch (line) {
    case 1:
      analogWrite(l1Pin, 0);
      break;
    case 2:
      analogWrite(l2Pin, 0);
      break;
    case 3:
      analogWrite(l3Pin, 0);
      break;
    case 4:
      analogWrite(l4Pin, 0);
      break;
    case 5:
      analogWrite(l5Pin, 0);
      break;
    case 6:
      analogWrite(l6Pin, 0);
      break;
    default:
      break;
  }
}
