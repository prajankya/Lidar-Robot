cmake_minimum_required(VERSION 2.8.3)

include_directories(${ROS_LIB_DIR})

generate_arduino_firmware(firmware
  BOARD mega2560
  SRCS ./firmware.cpp ${ROS_LIB_DIR}/time.cpp
  PORT /dev/ttyACM0
)
