#include "IMU.h"

void IMU::init(ros::NodeHandle _nh){
  nh = _nh;
  mag_sensor = Adafruit_HMC5883_Unified(12345);
  if(!mag_sensor.begin()) {
    while(1);
  }
  *imu_pub = ros::Publisher("imu", &imu_msg);
  nh.advertise(*imu_pub);
}
void IMU::loop(){
  sensors_event_t event;
  mag_sensor.getEvent(&event);
}
