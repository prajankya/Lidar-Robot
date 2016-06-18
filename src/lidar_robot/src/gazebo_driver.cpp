#include <ros/ros.h>
#include <ros/console.h>
#include <sensor_msgs/JointState.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "gazebo_driver");
  ros::NodeHandle nh;
  ros::Rate r(10);

  ros::Publisher wheel_state_pub = nh.advertise<sensor_msgs::JointState>("wheel_state", 10);

  sensor_msgs::JointState state;
  state.header.frame_id = "base_link";
  state.name.push_back("motor_shaft_1");
  state.name.push_back("motor_shaft_2");
  state.name.push_back("motor_shaft_3");
  state.name.push_back("motor_shaft_4");

  //state.position.resize(4);
  state.velocity.resize(4);
  //state.effort.resize(4);

  //state.position[0] = 30;
  state.velocity[1] = 30;
  //state.effort[2] = 20;

  while(nh.ok()) {
    state.header.stamp = ros::Time::now();
    state.velocity[3] += 0.2;
    wheel_state_pub.publish(state);
    //ROS_INFO_STREAM(state);
    r.sleep();
  }
}
