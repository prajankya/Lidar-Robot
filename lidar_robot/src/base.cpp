#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iomanip>
#include <tf/transform_broadcaster.h>
#include <std_msgs/String.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>

#include <ros/console.h>
#include <std_msgs/Bool.h>

tf::Quaternion quat;
tf::Vector3 vect;
int brake = 0, dir = 5, mag = 0;
ros::Time st;

double x=0, y=0, z=0;
double ar=0, ap=0, ay=0;

double absolute(double a){
  return std::abs(a);
}
void brakeReceived(const std_msgs::Bool &msg){
  st = ros::Time::now();
  brake = msg.data;
}

void twistReceived(const geometry_msgs::Twist &msg){
  double myX = 0, myY = 0, myRot = 0;
  double tol = 0.01;

  myX = msg.linear.x;
  myY = msg.linear.y;
  myRot = msg.angular.z;

  double a = 20 * 2;
  myX *= a;
  myY *= a;
  myRot *= a;

  if(absolute(myX) < tol  && absolute(myY) < tol){
    dir = 5;
  }

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
  ros::Publisher base_pub = nh.advertise<std_msgs::String>("Base_command", 50);

  ros::spinOnce();

  ros::Rate rate(10);

  //base.header.frame_id = "base_link";
  
  while(nh.ok()){
    ros::Duration  d(1);

    if(ros::Time::now() - st > d){
      st = ros::Time::now();
      dir = 5;
      mag = 0;
      brake = 1;
    }
	/*	std_msgs::String base=dir+","+mag+","+brake+"\n";
char numstr[21]; // enough to hold all numbers up to 64-bits
sprintf(numstr, "%d", age);
result = name + numstr;*/
//		std::string result = std::to_string (dir) + "," + std::to_string (mag) + "," + std::to_string (brake) + "\n";
		std::stringstream ss;
		ss << dir << "," << mag << "," << brake << "\n";
		std_msgs::String base;
		base.data = ss.str();

    base_pub.publish(base);

    ros::spinOnce();
    rate.sleep();
  }
}
