#define USE_IMU
#define USE_ODOM
#define USE_DESIGN
#define USE_BASE
#define USE_DEBUG

#include <Arduino.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include "BLDCOmni.h"

#ifdef USE_IMU
#include <sensor_msgs/MagneticField.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
//  #include "IMU.h"
#endif

#ifdef USE_ODOM
//  #include <nav_msgs/Odometry.h>
//  #include <tf/tf.h>
//  #include <tf/transform_broadcaster.h>
#include <Encoder.h>
#endif

#ifdef USE_DESIGN
#include <rosserial_arduino/Test.h>
#include "Design.h"
Design design;
#endif

#ifdef USE_BASE
BLDCOmni base;
#endif

ros::NodeHandle nh;

#ifdef USE_DEBUG
std_msgs::String str_msg;
ros::Publisher pub3("debug_out", &str_msg);
#endif

#ifdef USE_ODOM
//  geometry_msgs::TransformStamped odom;
//  tf::TransformBroadcaster odom_broadcaster;
std_msgs::String odom_msg;
ros::Publisher odom_pub("odom_feedback", &odom_msg);

Encoder theta(18, 22);
Encoder r(19, 23);

//  double pAng = 0.0;
//  double pLen = 0.0;

//  double odom_x = 0;
//  double odom_y = 0;
//  double odom_theta = 0;
#endif

#ifdef USE_BASE
int brake_ = 0;
int dir_ = 5;
int mag_ = 0;
bool brake = false;

void messageCb(const std_msgs::String &_cmd) {
  String ss = ((const char * ) _cmd.data);
  char s[ss.length() + 1];
  ss.toCharArray(s, ss.length() + 1);

  char *p = s;
  dir_ = String(strtok_r(p, ",", &p)).toInt();
  mag_ = String(strtok_r(p, ",", &p)).toInt();
  brake_ = String(strtok_r(p, ",", &p)).toInt();
}

ros::Subscriber<std_msgs::String> base_sub("Base_command", messageCb);
#endif

#ifdef USE_DESIGN
using rosserial_arduino::Test;
void animate_Design_callback(const Test::Request & req, Test::Response & res){
  String s = String(req.input);
  int type = s.toInt();
  design.animate(type);
}
ros::ServiceServer<Test::Request, Test::Response> server("animate_Design",&animate_Design_callback);
#endif

#ifdef USE_IMU
//  IMU imu(nh);
Adafruit_HMC5883_Unified mag_sensor = Adafruit_HMC5883_Unified(12345);
sensor_msgs::MagneticField mag;
ros::Publisher mag_pub("imu/mag", &mag);
#endif


void setup() {
  nh.initNode();

  #ifdef USE_DEBUG
  nh.advertise(pub3);
  #endif

  #ifdef USE_IMU
  //    imu.setup();
  if(!mag_sensor.begin()) {
    while(1);
  }
  nh.advertise(mag_pub);
  mag.header.frame_id = "imu_sensor";
  #endif

  #ifdef USE_DESIGN
  design.init(7, 8, 9, 10, 11, 12);//L1, L2, L3, L4, L5, L6
  nh.advertiseService(server);
  #endif

  #ifdef USE_ODOM
  nh.advertise(odom_pub);
  //    odom.header.frame_id = "odom";
  //    odom.child_frame_id = "base_link";
  //    odom_broadcaster.init(nh);
  #endif

  #ifdef USE_BASE
  nh.subscribe(base_sub);

  base.setMotor1(46, 50, 48, 52, 1); //speedPin, disablePin, directionPin, brakePin, speedFactor
  base.setMotor2(4, 42, 40, 44, 0.9);
  base.setMotor3(3, 34, 32, 36, 1);
  base.setMotor4(2, 26, 24, 28, 1);

  base.setDir(5);
  base.setMag(0);
  #endif
}

void loop() {
  #ifdef USE_IMU
  //    imu.loop();
  sensors_event_t event;
  mag_sensor.getEvent(&event);
  mag.header.stamp = nh.now();
  mag.magnetic_field.x = event.magnetic.x;
  mag.magnetic_field.y = event.magnetic.y;
  mag.magnetic_field.z = event.magnetic.z;

  mag_pub.publish(&mag);
  #endif

  #ifdef USE_ODOM
  long r_ = round(r.read() * 117.09);//multiplied by 10e5
  long t_ = round(theta.read() * 10471.9755);

  String s2 = "" + String(t_) + "," + String(r_);
  char bb2[50];
  s2.toCharArray(bb2, 50);
  odom_msg.data = bb2;
  odom_pub.publish(&odom_msg);

  /*
     odom.header.stamp = nh.now();

     double ang = theta.read() * 0.104719755;
     double len = r.read() * 0.0011709;

     double dLen = 0;
     double dAng = 0;

     if(pLen != len){
     dLen = len - pLen;
     pLen = len;
     }

     if(pAng != ang){
     dAng = ang - pAng;
     pAng = ang;
     }

     odom_x += cos(dAng) * dLen;
     odom_y += sin(dAng) * dLen;
     odom_theta += dAng;


     odom.transform.translation.x = odom_x;
     odom.transform.translation.y = odom_y;
     odom.transform.rotation = tf::createQuaternionFromYaw(0);//odom_theta);//ang);
     odom.header.stamp = nh.now();
     odom_broadcaster.sendTransform(odom);
   */
#endif

#ifdef USE_DEBUG
  String s = "dir = " + String(dir_) + "  mag=" + String(mag_) + " brake= " + String(brake_);
  char bb[50];
  s.toCharArray(bb, 50);
  str_msg.data = bb;
  pub3.publish(&str_msg);
#endif

  nh.spinOnce();

#ifdef USE_BASE
  if (brake_ && !brake) {
    base.brakeOn();
    brake = true;
  }

  if (brake && !brake_) {
    base.brakeOff();
    brake = false;
  }

  base.setDir(dir_);
  base.setMag(mag_);
#endif

  delay(10);
}
