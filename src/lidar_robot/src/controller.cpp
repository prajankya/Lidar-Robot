#include <ros/ros.h>
#include <std_srvs/Trigger.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <frontier_exploration/ExploreTaskAction.h>
#include <frontier_exploration/ExploreTaskActionGoal.h>

actionlib::SimpleActionClient<frontier_exploration::ExploreTaskAction> *ac;

bool startMapping(std_srvs::Trigger::Request  &req, std_srvs::Trigger::Response &res){
  /*res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);*/
  ROS_INFO("Waiting for action server to start.");
  // wait for the action server to start
  ac->waitForServer(); //will wait for infinite time

  ROS_INFO("Action server started, sending goal.");
  frontier_exploration::ExploreTaskGoal goal;

  goal.explore_center.header.frame_id = "map";
  goal.explore_center.header.stamp = ros::Time::now();
  goal.explore_boundary.header.frame_id = "map";
  goal.explore_boundary.header.stamp = ros::Time::now();
  goal.explore_center.point.x = 0;
  goal.explore_center.point.y = 0;
  goal.explore_center.point.z = 0;

  ac->sendGoal(goal);

  bool finished_before_timeout = ac->waitForResult(ros::Duration(30.0));

  if (finished_before_timeout) {
    actionlib::SimpleClientGoalState state = ac->getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
  }else{
    ROS_INFO("Action did not finish before the time out.");
  }

  return true;
}

int main(int argc, char **argv){
  ros::init(argc, argv, "Controller");
  ros::NodeHandle n;

  ros::ServiceServer startMappingService = n.advertiseService("startMapping", startMapping);
  actionlib::SimpleActionClient<frontier_exploration::ExploreTaskAction> a("explore_server", true);

  ac = &a;

  ROS_INFO("Ready to Start Mapping.");
  ros::spin();

  return 0;
}
