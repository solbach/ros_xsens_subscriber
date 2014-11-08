ROS xsens Subscriber
====================

Simple ROS Subscriber (C++) to read the xsens topics and write it to Disk (csv and json = not 100%)

* xsens driver are necessary [_LINK_](http://wiki.ros.org/action/fullsearch/xsens_driver?action=fullsearch&context=180&value=linkto%3A%22xsens_driver%22)
* Tested on ROS Hydro on Ubuntu 12.04 and ROS Indigo on Ubuntu 14.04
* Don't forget to set proper permissions: sudo chmod a+rw /dev/ttyUSB0
