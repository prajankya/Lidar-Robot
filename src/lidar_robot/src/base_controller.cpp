#include <ros/ros.h>
#include <ros/console.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>

ros::Time last_updated;

void twistReceived(const geometry_msgs::Twist &msg);

int main(int argc, char ** argv){
  ros::init(argc, argv, "base_controller");

  ROS_INFO_STREAM("Base Controller started");

  ros::NodeHandle nh;
  ros::Rate rate(10);

  ros::Subscriber base_sub = nh.subscribe("/cmd_vel", 20, &twistReceived);
  ros::Publisher base_pub = nh.advertise<std_msgs::String>("base_command", 20);

  while(nh.ok()) {

    ros::spinOnce();
    rate.sleep();
  }
}

void twistReceived(const geometry_msgs::Twist &msg){

}
