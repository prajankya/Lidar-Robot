#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iomanip>
#include <tf/transform_broadcaster.h>
#include <lidar_robot/Base_command.h>
#include <ros/console.h>
#include <std_msgs/Bool.h>

tf::Quaternion quat;
tf::Vector3 vect;
lidar_robot::Base_command base;

double x=0, y=0, z=0;
double ar=0, ap=0, ay=0;

double absolute(double a){
  return std::abs(a);
}
void brakeReceived(const std_msgs::Bool &msg){
  base.header.stamp = ros::Time::now();
  base.brake = msg.data;
}

void twistReceived(const geometry_msgs::Twist &msg){
  double myX = 0, myY = 0, myRot = 0;
  double factor = 0.05;
  double tol = 0.001;

  myX = msg.linear.x;
  myY = msg.linear.y;
  myRot = msg.angular.z;

  double a = 20;
  myX *= a;
  myY *= a;
  myRot *= a;

  int dir = 5;
  int mag = 0;

//TODO remove dummy 0 values
  if(absolute(myX) > tol  && absolute(myY) < tol && myX > tol){
    dir = 8;
  }
  
  if(absolute(myX) > tol  && absolute(myY) < tol && myX < -tol){
    dir = 2;
  }

  if(absolute(myX) < tol  && absolute(myY) > tol && myY > tol){
    dir = 4;
  }

  if(absolute(myX) < tol  && absolute(myY) > tol && myY < -tol){
    dir = 6;
  }

  if(absolute(myX) > tol  && absolute(myY) > tol && myX > tol && myY > tol){
    dir = 7;
  }

  if(absolute(myX) > tol  && absolute(myY) > tol && myX > tol && myY < -tol){
    dir = 9;
  }

  if(absolute(myX) > tol  && absolute(myY) > tol && myX < -tol && myY < -tol){
    dir = 3;
  }

  if(absolute(myX) > tol  && absolute(myY) > tol && myX < -tol && myY > tol){
    dir = 1;
  }
/*  if(absolute(myRot) > tol && myRot > tol){
    dir = '-';
  }
  if(absolute(myRot) > tol && myRot < tol){
    dir = '+';
  }
  */

  mag = floor(sqrt((myX * myX) + (myY * myY) + (myRot * myRot)));

//  ROS_INFO_STREAM("myX=" << myX << " dir=" << dir << " Mag =" << mag);
  
  base.header.stamp = ros::Time::now();
  base.direction = dir;
  base.magnitude = mag;
}

int main(int argc, char ** argv){
  ros::init(argc, argv, "base");

  ROS_INFO_STREAM("Base started Listening");

  ros::NodeHandle nh;

  ros::Subscriber brake_sub = nh.subscribe("base_brake", 1000, &brakeReceived);
  ros::Subscriber base_sub = nh.subscribe("/cmd_vel", 20, &twistReceived);
  ros::Publisher base_pub = nh.advertise<lidar_robot::Base_command>("Base_command", 50);

  ros::spinOnce();

  ros::Rate rate(10);

  base.header.frame_id = "base_link";
  
  while(nh.ok()){
    ros::Duration  d(1);

    if(ros::Time::now() - base.header.stamp < d){
      base_pub.publish(base);
    }else{
      base.header.stamp = ros::Time::now();
      base.direction = 5;
      base.magnitude = 0;
      base.brake = true;
      base_pub.publish(base);
    }

    ros::spinOnce();
    rate.sleep();
  }
}
