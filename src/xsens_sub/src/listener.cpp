#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/Imu.h"
#include <iostream>
#include <fstream>
#include <string>

std::ofstream myfile;

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
  ROS_INFO("Linear X = [%f]", lX);
  ROS_INFO("Linear Y = [%f]", lY);
  ROS_INFO("Linear Z = [%f]", lZ);
  ROS_INFO("Angular X = [%f]", aX);
  ROS_INFO("Angular Y = [%f]", aY);
  ROS_INFO("Angular Z = [%f]", aZ);

  myfile << std::to_string(msg->header.stamp.sec) + "." + std::to_string(msg->header.stamp.nsec) + ", ";
  myfile << std::to_string(lX) + ", ";
  myfile << std::to_string(lY) + ", ";
  myfile << std::to_string(lZ) + ", ";
  myfile << std::to_string(aX) + ", ";
  myfile << std::to_string(aY) + ", ";
  myfile << std::to_string(aZ) + "\n" << std::flush;

  //ros::Duration(1).sleep();
}

int main(int argc, char **argv)
{
  /*
  * Check if a path is provided
  **/
  if(argc < 2)
  {
  	ROS_ERROR("%s", "No Path provided");
  	return -1;
  }
  else
  {
	  ROS_INFO("%s", "Starting MAIN");

	  ros::init(argc, argv, "listener");

	  ros::NodeHandle n;

	  double secs =ros::Time::now().toSec();
	  ROS_INFO("%s", "opening");
	  std::string timeNow = std::to_string(secs);

	  try
	  {
	  	myfile.open(argv[1] + timeNow + ".csv");
	  }catch (const char* msg)
	  {
	  	std::cerr << "Error while opening output-stream: " << msg << std::endl;
	  }

	  myfile << "Time [sec], Linear x, Linear y, Linear z, Angular x, Angular y, Angular z \n";
	  ROS_INFO("%s", "Write");

	  ros::Subscriber sub = n.subscribe("imu/data", 1000, chatterCallback);

	  ros::spin();

	  ROS_INFO("%s", "close");
	  myfile.close();

	  return 0;
	}
}