#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <nav_msgs/Odometry.h>

#include <ros/console.h>
#include <std_msgs/Bool.h>

tf::Quaternion quat;
tf::Vector3 vect;
int brake = 0, dir = 5, mag = 0;
ros::Time st;

double x = 0, y = 0, z = 0;
double ar = 0, ap = 0, ay = 0;
double odom_x = 0;
double odom_y = 0;
double odom_theta = 0;
double priv_len = 0;
double priv_ang = 0;

geometry_msgs::TransformStamped odom_trans;
nav_msgs::Odometry odom;

double absolute(double a){
  return std::abs(a);
}

void brakeReceived(const std_msgs::Bool &msg){
  st = ros::Time::now();
  brake = msg.data;
}

double string_to_double( const std::string& s ){
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    return 0;
  return x;
}

void odomReceived(const std_msgs::String &msg){
  std::string input = msg.data;
  std::istringstream ss(input);
  std::string token;
  int i = 0;
  std::string in[3];

  while(std::getline(ss, token, ',')) {
    in[i++] = token;
  }

  int l = round(string_to_double(in[0]));
  int ang = round((fmod((string_to_double(in[1])), 24)) * 360 / 24);
  double heading = string_to_double(in[2]);

  double len = l * 0.0011709;
  //ROS_INFO_STREAM("received : " << ang << " deg  : " << len << " m");
  double dAng = 0,dLen = 0;

  if(priv_len!=len) {
    dLen = len - priv_len;
    priv_len = len;
  }
  if(priv_ang!=ang) {
    dAng = ang - priv_ang;
    priv_ang = ang;
  }
  //ROS_INFO_STREAM("received : " << dAng << " rad : " << dLen << " m");

  odom_theta += dAng;
  odom_x += cos(odom_theta) * dLen;
  odom_y += sin(odom_theta) * dLen;

  //ROS_INFO_STREAM("X:" << odom_x << " m \tY:" << odom_y << " m\tTheta:" << odom_theta);

  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(0);//imu_yaw

  odom_trans.transform.translation.x = odom_x;
  odom_trans.transform.translation.y = odom_y;
  odom_trans.transform.translation.z = 0.0;
  odom_trans.transform.rotation = odom_quat;

  //set the position
  odom.pose.pose.position.x = odom_x;
  odom.pose.pose.position.y = odom_y;
  odom.pose.pose.position.z = 0.0;
  odom.pose.pose.orientation = odom_quat;

/*  //set the velocity
   odom.twist.twist.linear.x = vx;
   odom.twist.twist.linear.y = vy;
   odom.twist.twist.angular.z = vth;*/
}

void twistReceived(const geometry_msgs::Twist &msg){
  double myX = 0, myY = 0, myRot = 0;
  double tol = 0.01;

  myX = msg.linear.x;
  myY = msg.linear.y;
  myRot = msg.angular.z;

  double a = 20 * 0.6;
  myX *= a;
  myY *= a;
  myRot *= a;

  if(absolute(myX) < tol  && absolute(myY) < tol) {
    dir = 5;
  }

  if(absolute(myX) > tol  && absolute(myY) < tol && myX > tol) {
    dir = 8;
  }

  if(absolute(myX) > tol  && absolute(myY) < tol && myX < -tol) {
    dir = 2;
  }

  if(absolute(myX) < tol  && absolute(myY) > tol && myY > tol) {
    dir = 4;
  }

  if(absolute(myX) < tol  && absolute(myY) > tol && myY < -tol) {
    dir = 6;
  }

  if(absolute(myX) > tol  && absolute(myY) > tol && myX > tol && myY > tol) {
    dir = 7;
  }

  if(absolute(myX) > tol  && absolute(myY) > tol && myX > tol && myY < -tol) {
    dir = 9;
  }

  if(absolute(myX) > tol  && absolute(myY) > tol && myX < -tol && myY < -tol) {
    dir = 3;
  }

  if(absolute(myX) > tol  && absolute(myY) > tol && myX < -tol && myY > tol) {
    dir = 1;
  }
/*  if(absolute(myRot) > tol && myRot > tol){
    dir = '-';
   }
   if(absolute(myRot) > tol && myRot < tol){
    dir = '+';
   }
 *//*
   double sinx = sin(myX);
   sinx = sinx * sinx;

   double siny = sin(myY);
   siny = siny * siny;

   double sinrot = sin(myRot);
   sinrot = sinrot * sinrot;
 */

  mag = floor(sqrt((myX * myX) + (myY * myY) + (myRot * myRot)));

//  ROS_INFO_STREAM("myX=" << myX << " dir=" << dir << " Mag =" << mag);

  st = ros::Time::now();
  // base.direction = dir;
  // base.magnitude = mag;
}

int main(int argc, char ** argv){
  ros::init(argc, argv, "base");

  ROS_INFO_STREAM("Base started Listening");

  ros::NodeHandle nh;

  ros::Subscriber brake_sub = nh.subscribe("base_brake", 1000, &brakeReceived);
  ros::Subscriber base_sub = nh.subscribe("/cmd_vel", 20, &twistReceived);
  ros::Subscriber odom_sub = nh.subscribe("odom_feedback", 20, &odomReceived);

  ros::Publisher base_pub = nh.advertise<std_msgs::String>("Base_command", 50);
  ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 50);
  tf::TransformBroadcaster odom_broadcaster;

  odom_trans.header.frame_id = "odom";
  odom_trans.child_frame_id = "base_link";
  odom.header.frame_id = "odom";
  odom.child_frame_id = "base_link";

  ros::spinOnce();

  ros::Rate rate(10);


  while(nh.ok()) {
    ros::Duration d(1);

    if(ros::Time::now() - st > d) {
      st = ros::Time::now();
      dir = 5;
      mag = 0;
      brake = 1;
    }
    brake = 0;

    std::stringstream ss;
    ss << dir << "," << mag << "," << brake << "\n";
    std_msgs::String base;
    base.data = ss.str();

    base_pub.publish(base);

    odom_trans.header.stamp = ros::Time::now();
    odom_broadcaster.sendTransform(odom_trans);
    //odom.header.stamp = ros::Time::now();
    //odom_pub.publish(odom);

    ros::spinOnce();
    rate.sleep();
  }
}
