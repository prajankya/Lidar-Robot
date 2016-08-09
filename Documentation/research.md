#Papers which are to be refered

###Mapping with Synthetic 2D LIDAR in 3D Urban Environment
>Z. J. Chong, B. Qin, T. Bandyopadhyay, M. H. Ang, E. Frazzoli, and D. Rus, “Mapping with synthetic 2D LIDAR in 3D urban environment,” in 2013 IEEE/RSJ International Conference on Intelligent Robots and Systems, 2013, pp. 4715–4720.

In this paper, we report a fully automated detailed
mapping of a challenging urban environment using single
LIDAR. To improve scan matching, extended correlative scan
matcher is proposed. Also, a Monte Carlo loop closure detec-
tion is implemented to perform place recognition efficiently.
Automatic recovery of the pose graph map in the presence of
false place recognition is realized through a heuristic based
loop closure rejection. This mapping framework is evaluated
through experiments on the real world dataset obtained from
NUS campus environment.

###2D LIDAR Aided INS for vehicle positioning in urban environments
>S. Zhao and J. A. Farrell, “2D LIDAR Aided INS for vehicle positioning in urban environments,” in 2013 IEEE International Conference on Control Applications (CCA), 2013, pp. 376–381.

This paper presents a novel method to utilize 2D LIDAR for INS (Inertial Navigation System) aiding to improve 3D vehicle position estimation accuracy, especially when GNSS signals are shadowed. In the proposed framework, 2D LIDAR aiding is carried out without imposing any assumptions on the vehicle motion (e.g. we allow full six degree-of freedom motion). To achieve this, a closed-form formula is derived to predict the line measurement in the LIDAR's frame. This makes the feature association, residual formation and GUI display possible. With this formula, the Extended Kalman Filter (EKF) can be employed in a straightforward manner to fuse the LIDAR and IMU data to estimate the full state of the vehicle. Preliminary experimental results show the effectiveness of the LIDAR aiding in reducing the state estimation uncertainty along certain directions, when GNSS signals are shadowed.

#Literature Reviews to be refered

###A Review and Analysis of Literature on Autonomous Driving
>by Juan Rosenzweig, Michael Bartl

###An Evaluation of 2D SLAM Techniques Available in Robot Operating System
>J. M. Santos, D. Portugal, and R. P. Rocha, “An evaluation of 2D SLAM techniques available in robot operating system,” in 2013 IEEE International Symposium on Safety, Security, and Rescue Robotics (SSRR), 2013, pp. 1–6.

In this work, a study of several laser-based 2D
Simultaneous Localization and Mapping (SLAM) techniques
available in Robot Operating System (ROS) is conducted. All
the approaches have been evaluated and compared in 2D
simulations and real world experiments. In order to draw
conclusions on the performance of the tested techniques, the
experimental results were collected under the same conditions
and a generalized performance metric based on the k-nearest
neighbors concept was applied. Moreover, the CPU load of each
technique is examined.
This work provides insight on the weaknesses and strengths
of each solution. Such analysis is fundamental to decide which
solution to adopt according to the properties of the intended
final application.


###Navigation stack test: GMapping vs Hector Slam
>P. da alesi, “Geduino Foundation: Navigation stack test: GMapping vs Hector Slam.”

[http://geduino.blogspot.com/2015/04/navigation-stack-test-gmapping-vs.html](http://geduino.blogspot.com/2015/04/navigation-stack-test-gmapping-vs.html)


#Technology(papers) being used in the Project

###Robot Web Tools: Efficient Messaging for Cloud Robotics

Since its official introduction in 2012, the Robot
Web Tools project has grown tremendously as an open-
source community, enabling new levels of interoperability and
portability across heterogeneous robot systems, devices, and
front-end user interfaces. At the heart of Robot Web Tools
is the rosbridge protocol as a general means for messaging
ROS topics in a client-server paradigm suitable for wide
area networks, and human-robot interaction at a global scale
through modern web browsers. Building from rosbridge, this
paper describes our efforts with Robot Web Tools to advance: 1)
human-robot interaction through usable client and visualization
libraries for more efficient development of front-end human-
robot interfaces, and 2) cloud robotics through more efficient
methods of transporting high-bandwidth topics (e.g., kinematic
transforms, image streams, and point clouds). We further
discuss the significant impact of Robot Web Tools through
a diverse set of use cases that showcase the importance of a
generic messaging protocol and front-end development systems
for human-robot interaction.


##Some other related Papers to think upon
- Y. Lin, J. Hyyppä, and A. Kukko, “Stop-and-Go Mode: Sensor Manipulation as Essential as Sensor Development in Terrestrial Laser Scanning,” Sensors, vol. 13, no. 7, pp. 8140–8154, Jun. 2013.  

- I. Baldwin and P. Newman, “Road vehicle localization with 2D push-broom LIDAR and 3D priors,” in 2012 IEEE International Conference on Robotics and Automation (ICRA), 2012, pp. 2611–2617.  

- Y. Ma, H. Ju, and P. Cui, “Research on Localization and Mapping for Lunar Rover Based on RBPF-SLAM,” in International Conference on Intelligent Human-Machine Systems and Cybernetics, 2009. IHMSC ’09, 2009, vol. 2, pp. 306–311.  

- R. Zlot and M. Bosse, “Place Recognition Using Keypoint Similarities in 2D Lidar Maps,” Experimental Robotics, pp. 363–372, 2009.  

- F. Auat Cheein, G. Steiner, G. Perez Paina, and R. Carelli, “Optimized EIF-SLAM algorithm for precision agriculture mapping based on stems detection,” Computers and Electronics in Agriculture, vol. 78, no. 2, pp. 195–207, Sep. 2011.  

- J. R. Rosell, J. Llorens, R. Sanz, J. Arnó, M. Ribes-Dasi, J. Masip, A. Escolà, F. Camp, F. Solanelles, F. Gràcia, E. Gil, L. Val, S. Planas, and J. Palacín, “Obtaining the three-dimensional structure of tree orchards from remote 2D terrestrial LIDAR scanning,” Agricultural and Forest Meteorology, vol. 149, no. 9, pp. 1505–1515, Sep. 2009.  

- W. Maddern, G. Pascoe, and P. Newman, “Leveraging experience for large-scale LIDAR localisation in changing cities,” in 2015 IEEE International Conference on Robotics and Automation (ICRA), 2015, pp. 1684–1691.  

- M. Himstedt, J. Frost, S. Hellbach, H. J. Böhme, and E. Maehle, “Large scale place recognition in 2D LIDAR scans using Geometrical Landmark Relations,” in 2014 IEEE/RSJ International Conference on Intelligent Robots and Systems, 2014, pp. 5030–5035.  

- J. M. Santos, D. Portugal, and R. P. Rocha, “An evaluation of 2D SLAM techniques available in robot operating system,” in 2013 IEEE International Symposium on Safety, Security, and Rescue Robotics (SSRR), 2013, pp. 1–6.  

- S. Kohlbrecher, O. von Stryk, J. Meyer, and U. Klingauf, “A flexible and scalable SLAM system with full 3D motion estimation,” in 2011 IEEE International Symposium on Safety, Security, and Rescue Robotics, 2011, pp. 155–160.  

- M. Vázquez-Arellano, H. W. Griepentrog, D. Reiser, and D. S. Paraforos, “3-D Imaging Systems for Agricultural Applications—A Review,” Sensors (Basel), vol. 16, no. 5, Apr. 2016.  

- J. McCormack, J. Prine, B. Trowbridge, A. C. Rodriguez, and R. Integlia, “2D LIDAR as a distributed interaction tool for virtual and augmented reality video games,” in 2015 IEEE Games Entertainment Media Conference (GEM), 2015, pp. 1–5.  

- S. Zhao and J. A. Farrell, “2D LIDAR Aided INS for vehicle positioning in urban environments,” in 2013 IEEE International Conference on Control Applications (CCA), 2013, pp. 376–381.  


## Surveys to refer
- A. Elkady, T. Sobh, A. Elkady, and T. Sobh, “Robotics Middleware: A Comprehensive Literature Survey and Attribute-Based Bibliography, Robotics Middleware: A Comprehensive Literature Survey and Attribute-Based Bibliography,” Journal of Robotics, Journal of Robotics, vol. 2012, 2012, p. e959013, May 2012.  

- S. Thrun and others, “Robotic mapping: A survey,” in Exploring artificial intelligence in the new millennium, vol. 1, 2002, pp. 1–35.  

## Thesis to consider

- C. F. Ezequiel, “Real-Time Map Manipulation for Mobile Robot Navigation,” 2013.  

- “kelly_alonzo_1994_7.pdf.” .  

- A. S. Khusheef, “Investigation on the mobile robot navigation in an unknown environment,” 2013.  
