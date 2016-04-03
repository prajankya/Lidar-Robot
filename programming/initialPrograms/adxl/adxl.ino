#include <Wire.h>
#include <ADXL345.h>

ADXL345 acc;

void setup(){
  acc.begin();
  acc.setRange(acc.RANGE_2G);
  Serial.begin(9600);
  delay(100);

  double Xg, Yg, Zg;
  acc.read(&Xg, &Yg, &Zg);
  acc.setZeroG(Xg,Yg,Zg);
}


void loop() {
  double Xg, Yg, Zg;
  acc.read(&Xg, &Yg, &Zg);

  Serial.print(Xg);
  Serial.print(",");
  Serial.print(Yg);
  Serial.print(",");
  Serial.println(Zg);
  
  delay(10);
}
