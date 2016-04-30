#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

#define pi 3.142

double wheel_dist=0.35521;

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n;

  ros::Rate r(10);

  tf::TransformBroadcaster broadcaster;

  while(n.ok()){
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0)),
        ros::Time::now(),"base_link", "imu_sensor"));

    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0)),
        ros::Time::now(),"map", "odom"));

/*    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0, 0, 0)),
        ros::Time::now(),"odom", "base_link"));
  */

      broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::createQuaternionFromRPY(pi/2, 0, 0), tf::Vector3(0, 0, 0.11675)),
        ros::Time::now(),"base_link", "rplidar"));
    
    broadcaster.sendTransform(
      tf::StampedTransform(
        tf::Transform(tf::createQuaternionFromRPY(pi/2, 0, 0), tf::Vector3(0, 0, 0)),
        ros::Time::now(),"rplidar", "laser_frame"));

    r.sleep();
  }
}
