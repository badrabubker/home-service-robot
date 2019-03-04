#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/String.h>
#include <string>
std::string strrin = "" ;
void status_callback(const std_msgs::String::ConstPtr& status)
{
//   status_str  = status->data.c_str() ;
//   ROS_INFO("status is %s" ,status->data.c_str());
   strrin = status->data.c_str() ;
}
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber status_subs = n.subscribe("/robot_status", 10, status_callback);
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::SPHERE;
  while (ros::ok())
  {
    ros::spinOnce();
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    visualization_msgs::Marker marker;
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
    if (strrin ==  "pickup" ){
        marker.action = visualization_msgs::Marker::DELETE;
    }

    if (strrin ==  "on the way" ){
        marker.action = visualization_msgs::Marker::DELETE;
    }
    if (strrin ==  "" ){

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -1.25;
    marker.pose.position.y = -2;
    marker.pose.position.z = 0.3;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    }

    if (strrin ==  "dropoff" ){

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -5.25;
    marker.pose.position.y = -2;
    marker.pose.position.z = 0.3;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
} 
   // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.20;
    marker.scale.y = 0.20;
    marker.scale.z = 0.20;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);

    r.sleep();
  }
}
