#include <ros/ros.h>
#include <ros/console.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
//#include <sstream>

double abs(double a);
void brakeReceived(const std_msgs::Bool &msg);
void twistReceived(const geometry_msgs::Twist &msg);

ros::Time last_updated;
int brake = 0, dir = 5, mag = 0;

int main(int argc, char ** argv){
  ros::init(argc, argv, "base_controller");

  ROS_INFO_STREAM("Base Controller started");

  ros::NodeHandle nh;
  ros::Rate rate(10);

  ros::Subscriber base_sub = nh.subscribe("/cmd_vel", 20, &twistReceived);
  ros::Subscriber brake_sub = nh.subscribe("base_brake", 100, &brakeReceived);

  ros::Publisher base_pub = nh.advertise<std_msgs::String>("base_command", 20);

  while(nh.ok()) {
    /*
       ros::Duration d(1);
       if(ros::Time::now() - st > d) {
       st = ros::Time::now();
       dir = 5;
       mag = 0;
       brake = 1;
       }
     */

    std::stringstream ss;
    ss << dir << "," << mag << "," << brake << "\n";
    std_msgs::String base;
    base.data = ss.str();

    base_pub.publish(base);

    ros::spinOnce();
    rate.sleep();
  }
}

void twistReceived(const geometry_msgs::Twist &msg){
  double tol = 0.01;

  double myX = msg.linear.x;
  double myY = msg.linear.y;
  double myRot = msg.angular.z;

  double a = 20 * 0.6;
  myX *= a;
  myY *= a;
  myRot *= a;

  if(abs(myX) < tol  && abs(myY) < tol) {
    dir = 5;
  }

  if(abs(myX) > tol  && abs(myY) < tol && myX > tol) {
    dir = 8;
  }

  if(abs(myX) > tol  && abs(myY) < tol && myX < -tol) {
    dir = 2;
  }

  if(abs(myX) < tol  && abs(myY) > tol && myY > tol) {
    dir = 4;
  }

  if(abs(myX) < tol  && abs(myY) > tol && myY < -tol) {
    dir = 6;
  }

  if(abs(myX) > tol  && abs(myY) > tol && myX > tol && myY > tol) {
    dir = 7;
  }

  if(abs(myX) > tol  && abs(myY) > tol && myX > tol && myY < -tol) {
    dir = 9;
  }

  if(abs(myX) > tol  && abs(myY) > tol && myX < -tol && myY < -tol) {
    dir = 3;
  }

  if(abs(myX) > tol  && abs(myY) > tol && myX < -tol && myY > tol) {
    dir = 1;
  }

  if(abs(myRot) > tol && myRot > tol) {
    dir = '-';
  }

  if(abs(myRot) > tol && myRot < tol) {
    dir = '+';
  }
  mag = (3*floor(sqrt((myX * myX) + (myY * myY) + (myRot * myRot))))+3;

  last_updated = ros::Time::now();
}

void brakeReceived(const std_msgs::Bool &msg){
  last_updated = ros::Time::now();
  brake = msg.data;
}

double abs(double a){
  return std::abs(a);
}
