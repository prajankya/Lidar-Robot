#include<Arduino.h>
#include "Design.h"

void Design::init(int _l1Pin, int _l2Pin, int _l3Pin, int _l4Pin, int _l5Pin, int _l6Pin) {
  l1Pin = _l1Pin;
  l2Pin = _l2Pin;
  l3Pin = _l3Pin;
  l4Pin = _l4Pin;
  l5Pin = _l5Pin;
  l6Pin = _l6Pin;

  analogWrite(l1Pin, 0);
  analogWrite(l2Pin, 0);
  analogWrite(l3Pin, 0);
  analogWrite(l4Pin, 0);
  analogWrite(l5Pin, 0);
  analogWrite(l6Pin, 0);
}

void Design::inOut(int inDelay) {
  for (int i = 0; i < 255; i += 5) {
    analogWrite(l1Pin, i);
    delay(inDelay);
  }
  for (int i = 0; i < 255; i += 5) {
    analogWrite(l2Pin, i);
    delay(inDelay);
  }
  for (int i = 0; i < 255; i += 5) {
    analogWrite(l3Pin, i);
    delay(inDelay);
  }
  for (int i = 0; i < 255; i += 5) {
    analogWrite(l4Pin, i);
    delay(inDelay);
  }
  for (int i = 0; i < 255; i += 5) {
    analogWrite(l5Pin, i);
    delay(inDelay);
  }
  for (int i = 0; i < 255; i += 5) {
    analogWrite(l6Pin, i);
    delay(inDelay);
  }

}
void Design::animate(int type){
  switch(type){
    case 1:
      inOut(2);
      break;
    case 2:
      outIn(2);
      break;
    case 3: //blink
      on();
      delay(50);
      off();
      delay(100);
      on();
      delay(50);
      off();
      break;
    case 4: //wave
      on(1);
      delay(50);
      on(2);
      off(1);
      delay(50);
      on(3);
      off(2);
      delay(50);
      on(4);
      off(3);
      delay(50);
      on(5);
      off(4);
      delay(50);
      on(6);
      off(5);
      delay(50);
      off(6);
      break;
    }
}


void Design::outIn(int inDelay) {
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(l6Pin, i);
    delay(inDelay);
  }
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(l5Pin, i);
    delay(inDelay);
  }
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(l4Pin, i);
    delay(inDelay);
  }
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(l3Pin, i);
    delay(inDelay);
  }
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(l2Pin, i);
    delay(inDelay);
  }
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(l1Pin, i);
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
