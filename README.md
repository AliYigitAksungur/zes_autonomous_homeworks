# ITU ZES Solar Car Team Autonomous Group - Homework 1
-----------------------------------------------------
## For 3 - Turtlesim and Keyboard Controller 
-----------------------------------------------------

### How to Setup Files: 

cd ./home/<user>/Documents/ 

mkdir –p turtle_ws/src 

colcon build 

cd ./src 

ros2 pkg create --build-type ament_cmake turtle_sim 

cd ./turtle_sim/src 

touch manual_turtle_control.cpp 

Copy codes to .cpp files, CMake and XML. 

cd ./home/<user>/Documents/turtle_ws/ 

colcon build 

-----------------------------------------------------

### How to Start Nodes 

Terminal 1:  

source /opt/ros/humble/setup.bash 

source install/setup.bash 

ros2 run turtlesim turtlesim_node


Terminal 2:  

source /opt/ros/humble/setup.bash 

source install/setup.bash 

ros2 run turtle_sim manual_turtle_control 

-----------------------------------------------------

### ROS Topics Used in Project: 

Terminal 1: 

source /opt/ros/humble/setup.bash 

source install/setup.bash 

ros2 topic list 

/parameter_events 

/rosout 

/turtle1/cmd_vel 

/turtle1/color_sensor 

/turtle1/pose 

-----------------------------------------------------
-----------------------------------------------------

## For 4 - Path Following with Stanley Controller: 

How to Setup Files: 

cd ./home/<user>/Documents/ 

mkdir –p stanley_ws/src 

colcon build 

cd ./src 

ros2 pkg create --build-type ament_cmake turtle_path_following 

cd ./turtle_path_following/src 

touch path_publisher.cpp 

touch stanley_controller.cpp 

Copy codes to .cpp files, CMake and XML. 

cd ./home/<user>/Documents/stanley_ws/ 

colcon build 

-----------------------------------------------------

### How to Start Nodes 

Terminal 1:  

source /opt/ros/humble/setup.bash 

source install/setup.bash 

ros2 run turtlesim turtlesim_node 


Terminal 2:  

source /opt/ros/humble/setup.bash 

source install/setup.bash 

ros2 run turtle_path_following path_publisher 


Terminal 3:  

source /opt/ros/humble/setup.bash 

source install/setup.bash 

ros2 run turtle_path_following stanley_controller. 


Terminal 4:  

source /opt/ros/humble/setup.bash 

source install/setup.bash 

rviz2  

-----------------------------------------------------

### ROS Topics Used in Project: 

Terminal 1: 

source /opt/ros/humble/setup.bash 

source install/setup.bash 

ros2 topic list 

/clicked_point 

/goal_pose 

/initialpose 

/parameter_events 

/path 

/rosout 

/tf 

/tf_static 

/turtle1/cmd_vel 

/turtle1/color_sensor 

/turtle1/pose 

/turtle_path 

-----------------------------------------------------

### Explanation of your Stanley Controller Implementation: 

The Stanley Controller steers the turtle to follow the path by combining two errors: 

Cross-Track Error: How far the turtle is from the path sideways. 

Heading Error: The difference between the turtle’s direction and the path’s direction.

----------------------------------------------------



 

