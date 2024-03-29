#!/bin/sh
catkin_dir=/home/workspace/catkin_ws
catkin_src_dir=$catkin_dir/src

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$catkin_src_dir/world/my_world.world " &
sleep 3

xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$catkin_src_dir/world/mymap.yaml " &

sleep 3
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch " &

sleep 8
xterm  -e  " rosrun add_markers add_markers "&
sleep 3

xterm -e " source $catkin_dir/devel/setup.bash; rosrun pick_objects pick_objects"
