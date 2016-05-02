#include <ros/ros.h>
#include <std_msgs/String.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/MagneticField.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <ros/console.h>

double ang = 0.0;
double len = 0.0;
double heading = 0.0;

void odomReceived(const std_msgs::String &msg){
//  msg.data
  std::vector<int> vect;
  std::stringstream ss(msg.data);

  int i;

  while(ss >> i){
    vect.push_back(i);
    if(ss.peek() == ','){
      ss.ignore();
    }
  }
  ang = vect.at(0) * 0.00001;
  len = vect.at(1) * 0.00001;

//  ROS_INFO("received %lf , %lf", r, t);
}

void magReceived(const sensor_msgs::MagneticField &msg){
  heading = atan2(msg.magnetic_field.y, msg.magnetic_field.x);

//  heading +=0.22; // Declination Angle
}

int main(int argc, char ** argv){
  ros::init(argc, argv, "odom_broadcaster");
  ros::NodeHandle nh;

  ros::Subscriber base_sub = nh.subscribe("odom_feedback", 20, &odomReceived);
  ros::Subscriber mag_pub = nh.subscribe("imu/mag", 20, &magReceived);

  ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 10);

  tf::TransformBroadcaster odom_broadcaster;

//  odom_broadcaster.init(nh);
/*
  double x = 0.0;
  double y = 0.0;
  double th = 0.0;

  double vx = 0.1;
  double vy = -0.1;
  double vth = 0.1;
*/
  double pAng = 0, pLen = 0;
  double odom_x = 0.0;
  double odom_y = 0.0;
  double odom_theta = 0.0;

  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Rate rate(5.0);
  while(nh.ok()){
    ros::spinOnce();// check for incoming messages
    current_time = ros::Time::now();

    double dAng = 0, dLen = 0;

    if(pAng != ang){
      dAng = ang - pAng;
      pAng = ang;
    }

    if(pLen != len){
      dLen = len - pLen;
      pLen = len;
    }

    odom_theta += dAng;
    odom_x += dLen * cos(heading - odom_theta);
    odom_y += dLen * sin(heading - odom_theta);

//    ROS_INFO("Heading : %lf", ((heading - odom_theta)*180/3.142));

    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = odom_x;

    odom_trans.transform.translation.y = odom_y;
    odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(heading);

    odom_broadcaster.sendTransform(odom_trans);

//    ROS_INFO(" x= %lf , y = %lf", odom_x, odom_y);
/*
    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

  */  //publish the message
//    odom_pub.publish(odom);

    last_time = current_time;
    rate.sleep();
  }


}
