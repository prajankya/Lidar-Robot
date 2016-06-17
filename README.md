[![DOI](https://zenodo.org/badge/22321/prajankya/Lidar-Robot.svg)](https://zenodo.org/badge/latestdoi/22321/prajankya/Lidar-Robot)


## Unmanned Mapping Vehicle Using L.O.A.M. in Real-time
 L.O.A.M. - Lidar Odometry and Mapping in Real-time

This project is about an Unmanned Mobile Robot using L.O.A.M. (Lidar, Odometry And Mapping) in Real-time.

##Abstract
The robot uses a Laser distance sensor(Lidar) which gives distance to the first obstacle in its line-of-sight and the sensor. Making this sensor rotate gives us distance of all the obstacles from the sensor, which in fact is the map of the surrounding. This sensor, with other sensors like odometry and IMU(Inertial measurement Unit), mounted on a mobile moving base and complex algorithms driving the robot autonomously help make a to-scale map of the surrounding.

##Basic contruction
The Bot uses ROS(Robot Operating System) at its core running on a compact mobile CPU. It uses IMU(Inertial measurement Unit) for its orientation feedback. The base comprise of a square frame with four omni wheel on its corners driven by high torque BLDC motors. The Bot works on 24v DC and have internal power distribution and conversion unit. The bot first takes in the lidar input, and process that into a map fusing together with  odometry input and IMU input. The Odometry sensor is a “Castor Feedback sensor” which consist of two rotary encoders, one reading the angle or rotation, and other the length in that direction. This type of feedback can be universally used for any type of terrain robots with very good accuracy. This bot can be controlled from a remote computer, on which we can even see the 3D Model and see the model within the map in Real time. The GUI remote can be used to save the map or load the map in the system. Taking all the properties in consideration,  Lidar Robot with L.O.A.M. is a very robust platform with variety of robotics applications.


##How to Install
rosdep install --from-paths /opt/ros/jade --ignore-src

rosdep install --from-paths Lidar-Robot/src --ignore-src

6th sem, 2017 Batch  
Department of Automation and Robotics.  
B. V. Bhoomaraddi College of Engineering and Technology, Hubli  

##Robot Geometrical Info
>
Mesh Bounding Box Size 0.726000 0.153518 0.728274
Mesh Bounding Box Diag 1.039725
Mesh Volume is 0.007492
Mesh Surface is 2.565935
Thin shell barycenter 0.000109 0.009018 -0.000083
Center of Mass is 0.000050 0.006649 -0.000088
Inertia Tensor is :
| 0.000231 -0.000000 0.000000 |
| -0.000000 0.000439 -0.000000 |
| 0.000000 -0.000000 0.000230 |
Principal axes are :
| 0.999454 -0.000068 -0.033026 |
| 0.000068 1.000000 -0.000001 |
| 0.033026 -0.000001 0.999454 |
axis momenta are :
| 0.000231 0.000439 0.000230 |

##Wheel Geometrical Info
>
Mesh Bounding Box Size 0.149237 0.038020 0.148513
Mesh Bounding Box Diag 0.213947
Mesh Volume is 0.000238
Mesh Surface is 0.093921
Thin shell barycenter 0.000002 -0.005367 0.000031
Center of Mass is 0.000001 -0.005476 0.000028
Inertia Tensor is :
| 0.000000 0.000000 0.000000 |
| 0.000000 0.000001 0.000000 |
| 0.000000 0.000000 0.000000 |
Principal axes are :
| 0.863798 0.000013 0.503839 |
| 0.000080 1.000000 -0.000163 |
| -0.503839 0.000181 0.863798 |
axis momenta are :
| 0.000000 0.000001 0.000000 |


>
##Team 9
- [Adarsh Belavatagi](http://github.com/Belavatagi)
- [Darshan Bafna](http://github.com/Darshabafna)
- [Manikanta Pujar](http://github.com/pujarmani)
- [Prajankya Sonar](http://github.com/Prajankya)
