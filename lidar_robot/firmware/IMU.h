#ifndef __IMU_H__
#define __IMU_H__

#include <Arduino.h>
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Temperature.h>
#include <sensor_msgs/FluidPressure.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085_U.h>
#include <L3G4200D.h>

class IMU{
private:
  ros::NodeHandle nh;
  Adafruit_HMC5883_Unified mag_sensor;
  Adafruit_ADXL345_Unified accel_sensor;
  Adafruit_BMP085_Unified bmp_sensor;

  sensor_msgs::MagneticField mag;
  sensor_msgs::Imu imu;
  sensor_msgs::Temperature temperature;
  sensor_msgs::FluidPressure pressure;

  L3G4200D gyroscope;

  ros::Publisher mag_pub;
  ros::Publisher imu_pub;
  ros::Publisher temperature_pub;
  ros::Publisher pressure_pub;
public:
  IMU(ros::NodeHandle _nh);
  void setup();
  void loop();
};
#endif