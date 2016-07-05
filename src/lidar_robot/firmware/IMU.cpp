#include "IMU.h"
#include <Arduino.h>

void IMU::init(ros::NodeHandle _nh, const char * topic){
  nh = _nh;
  mag_sensor = Adafruit_HMC5883_Unified(12345);

  if(!mag_sensor.begin()) {
    while(1){
      Serial.println("Ooops, no IMU detected ... Check your wiring!");
    }
  }

  ros::Publisher imu_pub_(topic, &imu_msg);
  imu_pub = &imu_pub_;
  nh.advertise(*imu_pub);
}
void IMU::loop(){
  sensors_event_t event;
  mag_sensor.getEvent(&event);

  char x[10];
  dtostrf(event.magnetic.x, 6, 2, x);

  char y[10];
  dtostrf(event.magnetic.y, 6, 2, y);

  char z[10];
  dtostrf(event.magnetic.z, 6, 2, z);

  String s = String(x)+","+String(y)+","+String(z);
  char bb[50];
  s.toCharArray(bb, 50);
  imu_msg.data = bb;
  imu_pub->publish(&imu_msg);
}
