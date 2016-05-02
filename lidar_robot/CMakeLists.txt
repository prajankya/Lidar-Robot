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
)

catkin_package(
  CATKIN_DEPENDS 
  std_msgs
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

add_executable(base src/base.cpp)
target_link_libraries(base ${catkin_LIBRARIES})

add_executable(tf_broadcaster src/tf_broadcaster.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})

add_executable(odom_broadcaster src/odom_broadcaster.cpp)
target_link_libraries(odom_broadcaster ${catkin_LIBRARIES})
