#define USE_FEEDBACK
//#define USE_DESIGN
#define USE_BASE
#define USE_DEBUG

#include <Arduino.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include "BLDCOmni.h"

#ifdef USE_FEEDBACK
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Encoder.h>

Adafruit_HMC5883_Unified mag_sensor = Adafruit_HMC5883_Unified(12345);
std_msgs::String feedback_msg;
ros::Publisher feedback_pub("feedback", &feedback_msg);

Encoder theta(18, 22);
Encoder r(19, 23);
#endif

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
}

ros::Subscriber<std_msgs::String> base_sub("Base_command", messageCb);
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

#ifdef USE_FEEDBACK
  if(!mag_sensor.begin()) {
    while(1) {
      Serial.println("Ooops, no IMU detected ... Check your wiring!");
    }
  }
  nh.advertise(feedback_pub);
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
#ifdef USE_FEEDBACK
  sensors_event_t event;
  mag_sensor.getEvent(&event);

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);

  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -0° 55' W, which is 0 Degrees, or (which we need) 0 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  /*float declinationAngle = 0;
     heading += declinationAngle;*/

  // Correct for when signs are reversed.
  if(heading < 0) {
    heading += 2 * PI;
  }

  // Check for wrap due to addition of declination.
  if(heading > 2 * PI) {
    heading -= 2 * PI;
  }

  char x[10];
  dtostrf(heading, 6, 4, head);
  String s1 = String(r.read()) + "," + String(t.read()) + "," + String(head);
  char bb[50];
  s1.toCharArray(bb, 50);
  feedback_msg.data = bb;
  feedback_pub.publish(&feedback_msg);
#endif

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

  base.setDir(dir_);
  base.setMag(mag_);
#endif

  delay(10);
}
