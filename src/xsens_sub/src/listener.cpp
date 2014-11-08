#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/Imu.h"
//#include "geometry_msgs/TwistStamped.h"
#include <iostream>
#include <fstream>
#include <string>

int first = 0;
std::ofstream myfile;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
/*void chatterCallback2(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
  ROS_INFO("Angular X = [%f]", msg->twist.angular.x);
  ROS_INFO("Angular Y = [%f]", msg->twist.angular.y);
  ROS_INFO("Angular Z = [%f]", msg->twist.angular.z);

  ROS_INFO("Linear X = [%f]", msg->twist.linear.x);
  ROS_INFO("Linear Y = [%f]", msg->twist.linear.x);
  ROS_INFO("Linear Z = [%f]", msg->twist.linear.x);

}*/

void chatterCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
  double aX = msg->angular_velocity.x;
  double aY = msg->angular_velocity.y;
  double aZ = msg->angular_velocity.z;

  double lX = msg->linear_acceleration.x;
  double lY = msg->linear_acceleration.y;
  double lZ = msg->linear_acceleration.z;

  ROS_INFO("Stamp sec= [%d]", msg->header.stamp.sec);
  ROS_INFO("Stamp nsec= [%d]", msg->header.stamp.nsec);
  ROS_INFO("Angular X = [%f]", msg->angular_velocity.x);
  ROS_INFO("Angular Y = [%f]", msg->angular_velocity.y);
  ROS_INFO("Angular Z = [%f]", msg->angular_velocity.z);

  ROS_INFO("Linear X = [%f]", msg->linear_acceleration.x);
  ROS_INFO("Linear Y = [%f]", msg->linear_acceleration.y);
  ROS_INFO("Linear Z = [%f]", msg->linear_acceleration.z);

  myfile << " \t \"Timestamp\" : { \n \t \t\"sec\" : "+ std::to_string(msg->header.stamp.sec) + ", \n \t \t \"nsec\" : "+ std::to_string(msg->header.stamp.nsec) + "\n \t }, \n";
  myfile << " \t \"Linear\" : { \n \t \t\"x\" : "+ std::to_string(msg->linear_acceleration.x) + ", \n \t \t \"y\" : "+ std::to_string(msg->linear_acceleration.y) + ", \n \t \t \"z\" : "+ std::to_string(msg->linear_acceleration.z) + "\n \t }, \n";
  myfile << " \t \"Angular\" : { \n \t \t\"x\" : "+ std::to_string(msg->angular_velocity.x) + ", \n \t \t \"y\" : "+ std::to_string(msg->angular_velocity.y) + ", \n \t \t \"z\" : "+ std::to_string(msg->angular_velocity.z) + "\n \t }, \n"  << std::flush;

  ros::Duration(1).sleep();
}

int main(int argc, char **argv)
{
  ROS_INFO("%s", "Starting MAIN");
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  ROS_INFO("%s", "opening");
  double secs =ros::Time::now().toSec();
  std::string timeNow = std::to_string(secs);

  myfile.open(timeNow + ".json");

  ROS_INFO("%s", "Write");
  myfile << "{\n";
  myfile << " \"Date\" : \"" + timeNow + "\", \n";
  myfile << " \"Type\" : \"xsens\", \n";
  myfile << " \"Data\" : [ \n { \n";

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  //ros::Subscriber sub2 = n.subscribe("velocity", 1000, chatterCallback2);
  ros::Subscriber sub = n.subscribe("imu/data", 1000, chatterCallback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  ROS_INFO("%s", "close");
  myfile << " } \n ] \n }";
  myfile.close();

  return 0;
}
