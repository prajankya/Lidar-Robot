#ifndef _IMU_H_
#define _IMU_H_

#include<Arduino.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_HMC5883_U.h>
#include<ros.h>
#include<ros/time.h>
#include<std_msgs/String.h>

class IMU {
  private:
    ros::NodeHandle nh;
    std_msgs::String imu_msg;
    ros::Publisher * imu_pub;
    Adafruit_HMC5883_Unified mag_sensor;

  public:
    void init(ros::NodeHandle _nh, const char * topic);
    void loop();
};


#endif
