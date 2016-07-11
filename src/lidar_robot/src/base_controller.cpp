#include <ros/ros.h>

int main(int argc, char ** argv){
  ros::init(argc, argv, "base_controller");

  ROS_INFO_STREAM("Base Controller started");

  ros::NodeHandle nh;
  ros::Rate rate(10);

  while(nh.ok()) {

    ros::spinOnce();
    rate.sleep();
  }
}
