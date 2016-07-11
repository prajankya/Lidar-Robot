//#define USE_DESIGN
#define USE_BASE
#define USE_DEBUG

#include <Arduino.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include "BLDCOmni.h"

#ifdef USE_DESIGN
#include <rosserial_arduino/Test.h>
#include "Design.h"
Design design;
using rosserial_arduino::Test;
void animate_Design_callback(const Test::Request & req, Test::Response & res){
  String s = String(req.input);
  int type = s.toInt();
  design.animate(type);
}
ros::ServiceServer<Test::Request, Test::Response> server("animate_Design",&animate_Design_callback);
#endif

#ifdef USE_BASE
BLDCOmni base;
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

  mag_ = constrain(mag_, 0, 30);
}

ros::Subscriber<std_msgs::String> base_sub("base_command", messageCb);
#endif

ros::NodeHandle nh;

#ifdef USE_DEBUG
std_msgs::String str_msg;
ros::Publisher pub3("debug_out", &str_msg);
#endif

void setup() {// ----------------------------------------- setup
  nh.initNode();
#ifdef USE_DEBUG
  nh.advertise(pub3);
#endif

#ifdef USE_DESIGN
  design.init(7, 8, 9, 10, 11, 12);//L1, L2, L3, L4, L5, L6
  nh.advertiseService(server);
#endif

#ifdef USE_BASE
  nh.subscribe(base_sub);

  base.setMotor1(46, 50, 48, 52, 1); //speedPin, disablePin, directionPin, brakePin, speedFactor
  base.setMotor2(4, 42, 40, 44, 1);
  base.setMotor3(3, 34, 32, 36, 1);
  base.setMotor4(2, 26, 24, 28, 1);

  base.setDir(5);
  base.setMag(0);
#endif
}

void loop() {
#ifdef USE_DEBUG
  String s = "dir = " + String(dir_) + "  mag=" + String(mag_) + " brake= " + String(brake_);
  char bb3[50];
  s.toCharArray(bb3, 50);
  str_msg.data = bb3;
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

//  base.setDir(dir_);
//  base.setMag(mag_);
#endif

  delay(10);
}
