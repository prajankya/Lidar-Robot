#include "ros/ros.h"
#include <std_srvs/Empty.h>
#include <cstdlib>

int main(int argc, char **argv){
  ros::init(argc, argv, "masterStart");
/*  if (argc != 3)
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }*/

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<std_srvs::Empty>("/lidar_robot/stop_motor");
  std_srvs::Empty srv;

  ros::Duration(0.5).sleep();
  if (client.call(srv)){
    ROS_INFO("Motor stop called");
  }
  else
  {
    ROS_ERROR("Failed to call service ");
    return 1;
  }

  return 0;
}
