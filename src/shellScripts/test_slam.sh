catkin_dir=/home/workspace/catkin_ws
catkin_src_dir=$catkin_dir/src

#Launch turtlebot in the custom world
xterm  -e  "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/world/my_world.world" &
sleep 2

#Launch gmapping demo
xterm -e "roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 2

#Launch turtlebot teleop
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch" &
sleep 2

#Launch rviz
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch"

