cmake_minimum_required(VERSION 2.8.3)
project(lidar_robot)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  std_srvs
  geometry_msgs
  tf
  nav_msgs
  rosserial_arduino
  rosserial_client
	frontier_exploration
)

catkin_package(
  CATKIN_DEPENDS
  std_msgs
	frontier_exploration
)

rosserial_generate_ros_lib(
  PACKAGE rosserial_arduino
  SCRIPT make_libraries.py
)

rosserial_configure_client(
  DIRECTORY firmware
  TOOLCHAIN_FILE ${ROSSERIAL_ARDUINO_TOOLCHAIN}
)

rosserial_add_client_target(firmware firmware ALL)
rosserial_add_client_target(firmware firmware-upload)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#add_executable(explorer src/explorer.cpp)
#target_link_libraries(explorer ${catkin_LIBRARIES})

add_executable(controller src/controller.cpp)
target_link_libraries(controller ${catkin_LIBRARIES})
add_dependencies(controller std_srvs)
