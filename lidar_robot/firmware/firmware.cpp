#include <Arduino.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Temperature.h>
#include <sensor_msgs/FluidPressure.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP085_U.h>
#include <L3G4200D.h>
#include <Encoder.h>

#include"BLDCOmni.h"
#include "Design.h"

Design design;
BLDCOmni base;

Adafruit_HMC5883_Unified mag_sensor = Adafruit_HMC5883_Unified(11);
Adafruit_ADXL345_Unified accel_sensor = Adafruit_ADXL345_Unified(22);
Adafruit_BMP085_Unified bmp_sensor = Adafruit_BMP085_Unified(10085);

ros::NodeHandle nh;

sensor_msgs::MagneticField mag;
sensor_msgs::Imu imu;
sensor_msgs::Temperature temperature;
sensor_msgs::FluidPressure pressure;

geometry_msgs::TransformStamped odom;
tf::TransformBroadcaster odom_broadcaster;

L3G4200D gyroscope;
std_msgs::String str_msg;

ros::Publisher pub("imu/mag", &mag);
ros::Publisher pub2("/imu", &imu);
ros::Publisher pub3("debug_out", &str_msg);
ros::Publisher pub4("temperature", &temperature);
ros::Publisher pub5("pressure", &pressure);

Encoder r(18, 22);
Encoder theta(19, 23);

double odom_x = 0;
double odom_y = 0;
double odom_angle = 0;

int brake_ = 0;
int dir_ = 5;
int mag_ = 0;

void messageCb( const std_msgs::String &_cmd) {
  String ss = ((const char * ) _cmd.data);
  char s[ss.length() + 1];
  ss.toCharArray(s, ss.length() + 1);

  char *p = s;
  dir_ = String(strtok_r(p, ",", &p)).toInt();
  mag_ = String(strtok_r(p, ",", &p)).toInt();
  brake_ = String(strtok_r(p, ",", &p)).toInt();
}

ros::Subscriber<std_msgs::String> base_sub("Base_command", messageCb);

double azx = 0, azy = 0, azz = 0;
bool brake = false;

void setup() {
  nh.initNode();
  nh.advertise(pub);
  nh.advertise(pub2);
  nh.advertise(pub3);
  nh.advertise(pub4);
  nh.advertise(pub5);

  odom_broadcaster.init(nh);

  nh.subscribe(base_sub);

  base.setMotor1(46, 50, 48, 52, 1); //speedPin, disablePin, directionPin, brakePin, speedFactor
  base.setMotor2(4, 42, 40, 44, 1);
  base.setMotor3(3, 34, 32, 36, 1);
  base.setMotor4(2, 26, 24, 28, 1);

  base.setDir(5);
  base.setMag(0);

  design.init(12, 11, 10, 9, 8, 7);//L1, L2, L3, L4, L5, L6

  mag.header.frame_id = "imu_sensor";
  imu.header.frame_id = "imu_sensor";
  temperature.header.frame_id = "imu_sensor";
  odom.header.frame_id = "odom";
  odom.child_frame_id = "base_link";
  pressure.header.frame_id = "imu_sensor";

  if (!mag_sensor.begin()) {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }

  while (!gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_400HZ_50)) {

  }
  gyroscope.calibrate(100);

  if (!accel_sensor.begin()) {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }
  accel_sensor.setRange(ADXL345_RANGE_2_G);

  if (!bmp_sensor.begin()) {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  imu.orientation.x = 0.0;
  imu.orientation.y = 0.0;
  imu.orientation.z = 0.0;
  imu.orientation.w = 1.0;

  design.inOut(10);
}

void loop() {
  sensors_event_t event;
  mag_sensor.getEvent(&event);

  mag.header.stamp = nh.now();
  mag.magnetic_field.x = -event.magnetic.x;
  mag.magnetic_field.y = -event.magnetic.y;
  mag.magnetic_field.z = event.magnetic.z;

  pub.publish(&mag);

  sensors_event_t event2;
  accel_sensor.getEvent(&event2);

  Vector norm = gyroscope.readNormalize();

  imu.header.stamp = nh.now();
  imu.angular_velocity.x = norm.XAxis;
  imu.angular_velocity.y = norm.YAxis;
  imu.angular_velocity.z = norm.ZAxis;

  imu.linear_acceleration.x = (event2.acceleration.x - azx);
  imu.linear_acceleration.y = (event2.acceleration.y - azy);
  imu.linear_acceleration.z = (event2.acceleration.z - azz);

  pub2.publish(&imu);

  //  String s2 = String(cmd.magnitude);
  String s = "dir = " + String(dir_) + "  mag=" + String(mag_) + " brake= " + String(brake_);
  char bb[50];
  s.toCharArray(bb, 50);
  str_msg.data = bb;
  pub3.publish(&str_msg);

  odom.header.stamp = nh.now();
  /*
    odom.pose.pose.position.x = 0.0;
    odom.pose.pose.position.y = 0.0;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = tf::createQuaternionFromYaw(0);

    odom.twist.twist.linear.x = 0.0;
    odom.twist.twist.linear.y = 0.0;
    odom.twist.twist.linear.z = 0.0;

    odom.twist.twist.angular.x = 0.0;
    odom.twist.twist.angular.y = 0.0;
    odom.twist.twist.angular.z = 0.0;
  */

  double dAng = 0;//change in angle
  double dlen = 0;//change in length

  odom_x += dlen * cos(dAng);
  odom_y += dlen * sin(dAng);
  odom_angle += dAng;

  odom.transform.translation.x = odom_x;
  odom.transform.translation.y = odom_y;

  odom.transform.rotation = tf::createQuaternionFromYaw(odom_angle);
  odom.header.stamp = nh.now();
  odom_broadcaster.sendTransform(odom);

  temperature.header.stamp = nh.now();
  float temp;
  bmp_sensor.getTemperature(&temp);
  temperature.temperature = temp;
  pub4.publish(&temperature);

  sensors_event_t event3;
  bmp_sensor.getEvent(&event3);
  if (event.pressure) {
    pressure.header.stamp = nh.now();
    pressure.fluid_pressure = event3.pressure;
    pub5.publish(&pressure);
  }

  nh.spinOnce();
  /*
    if (cmd.brake && !brake) {
      base.brakeOn();
      brake = true;
    }

    if (brake && !cmd.brake) {
      base.brakeOff();
      brake = false;
    }

    base.setDir(cmd.direction);
    base.setMag(cmd.magnitude);
  */
  delay(10);
}
