#include"BLDCOmni.h"

BLDCOmni base(46, 14);//speedPin,BrakePin

const unsigned int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  base.setMotor1(17, 16, 2, 0.49);//disablePin,directionPin,tachoPin
  base.setMotor2(34, 36, 3, 0.49);
  base.setMotor3(38, 40, 4, 0.59);
  base.setMotor4(42, 44, 5, 0.91);

  base.setDir(5);
  base.setMag(0);

  Serial.begin(19200);
}

void loop() {
  checkSerialForData();
}
void checkSerialForData() {
  if (Serial.available() > 0) {
    int dir = Serial.parseInt();
    int mag = Serial.parseInt();
    if (Serial.read() == '\n') {
      base.setDir(dir);
      base.setMag(mag);
    }
  }
}

