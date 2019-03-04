#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/String.h>
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  ros::Publisher status_pub = n.advertise<std_msgs::String>("/robot_status", 10);
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pick_up;

  // set up the frame parameters
  pick_up.target_pose.header.frame_id = "map";
  pick_up.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pick_up.target_pose.pose.position.x = -1.25;
  pick_up.target_pose.pose.position.y = -2.0;
  pick_up.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick up ");
  ac.sendGoal(pick_up);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, i reached the Pick up Location");
    std_msgs::String msg;
    msg.data="pickup";
    status_pub.publish(msg);
    ros::Duration(5.0).sleep();
  }else{
    ROS_INFO("coudn't get to pick up location");
  }
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -5.25;
  goal.target_pose.pose.position.y = -2.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off");
  ac.sendGoal(goal);
  std_msgs::String msg;
  msg.data="on the way";
  status_pub.publish(msg);
  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, i reached the drop off Location");
    std_msgs::String msg;
    msg.data="dropoff";
    status_pub.publish(msg);
  }else{
    ROS_INFO("coudn't get to drop off location");
  }
  return 0;
}
