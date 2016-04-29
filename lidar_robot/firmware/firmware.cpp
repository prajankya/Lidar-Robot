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
  #include "IMU.h"
#endif

#ifdef USE_ODOM
  #include <nav_msgs/Odometry.h>
  #include <tf/tf.h>
  #include <tf/transform_broadcaster.h>
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
  geometry_msgs::TransformStamped odom;
  tf::TransformBroadcaster odom_broadcaster;

  Encoder theta(18, 22);
  Encoder r(19, 23);

  double odom_x = 0;
  double odom_y = 0;
  double odom_angle = 0;
#endif

#ifdef USE_BASE
  int brake_ = 0;
  int dir_ = 5;
  int mag_ = 0;
  bool brake = false;

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
#endif

#ifdef USE_DESIGN
  using rosserial_arduino::Test;
  void animate_Design_callback(const Test::Request & req, Test::Response & res){
    String s = String(req.input);
    int type = s.toInt();

    switch(type){
      case 1:
      design.inOut(2);
      break;
      case 2:
      design.outIn(2);
      break;
      case 3: //blink
      design.on();
      delay(50);
      design.off();
      delay(100);
      design.on();
      delay(50);
      design.off();
      break;
      case 4: //wave
      design.on(1);
      delay(50);
      design.on(2);
      design.off(1);
      delay(50);
      design.on(3);
      design.off(2);
      delay(50);
      design.on(4);
      design.off(3);
      delay(50);
      design.on(5);
      design.off(4);
      delay(50);
      design.on(6);
      design.off(5);
      delay(50);
      design.off(6);
      break;
    }
  }
  ros::ServiceServer<Test::Request, Test::Response> server("animate_Design",&animate_Design_callback);
#endif

#ifdef USE_IMU
  IMU imu(nh);
#endif


void setup() {
  nh.initNode();

  #ifdef USE_DEBUG
    nh.advertise(pub3);
  #endif

  #ifdef USE_IMU
    imu.setup();
  #endif

  #ifdef USE_DESIGN
    design.init(7, 8, 9, 10, 11, 12);//L1, L2, L3, L4, L5, L6
    nh.advertiseService(server);
  #endif

  #ifdef USE_ODOM
  odom.header.frame_id = "odom";
  odom.child_frame_id = "base_link";
  odom_broadcaster.init(nh);
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
  #ifdef USE_IMU
  imu.loop();
  #endif

  #ifdef USE_ODOM
    odom.header.stamp = nh.now();

    double ang = theta.read() * 0.104719755;//change in angle
    double len = r.read() * 0.0011709;//change in length
          
    odom.transform.translation.x = cos(ang) * len;
    odom.transform.translation.y = sin(ang) * len;
    odom.transform.rotation = tf::createQuaternionFromYaw(ang);
    odom.header.stamp = nh.now();
    odom_broadcaster.sendTransform(odom);

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
