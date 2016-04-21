cmake_minimum_required(VERSION 2.8.3)

include_directories(${ROS_LIB_DIR})
include_directories(~/Arduino/libraries/ros_lib)
generate_arduino_firmware(firmware
  BOARD uno
  SRCS ./firmware.cpp ${ROS_LIB_DIR}/time.cpp
  PORT /dev/ttyACM0
)
