ROS xsens plotter and recorder
==============================

Simple ROS Subscriber (C++) to read the xsens topics and record them as csv.
Furthermore, it starts rqt_plot instances to show current data graphically.


* xsens driver are necessary [_LINK_](http://wiki.ros.org/action/fullsearch/xsens_driver?action=fullsearch&context=180&value=linkto%3A%22xsens_driver%22)
* Tested on ROS Hydro on Ubuntu 12.04 and ROS Indigo on Ubuntu 14.04
* Do the following steps to run it 
	1. _$ catkin_make_
	1. _$ sudo chmod a+rw /dev/ttyUSB0_
	1. _$ source devel/setup.bash_
	1. _$ roslauch xsens_sub xsensPR.launch_
	1. _$ rosrun xsens_sub xsens_listen_