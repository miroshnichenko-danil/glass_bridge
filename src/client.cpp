#include "ros/ros.h"
#include "glass_bridge/glass_bridge.h"
#include <iostream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "glass_bridge_publisher");

  ros::NodeHandle n;
  ros::ServiceClient client=n.serviceClient<glass_bridge::glass_bridge>("glass_bridge");
  glass_bridge::glass_bridge srv;

  while (ros::ok())
  {
    std::string a;
    std::cout << "choose left or right tile:";    
    std::cin >> a;
    if (a != "l" && a != "r")
    {
      std::cout << "False" << std::endl;
      continue;
    }
    srv.request.input = a;
    if (srv.response.output == "dead")
    {
      ROS_INFO_STREAM("dead");
      ros::shutdown();
    } 
    if (srv.response.output.length() == 17)
    {
      ROS_INFO_STREAM("Congratulations, you won");
      ros::shutdown();
    }
    std::cout << "your path:" << srv.response.output << std::endl;
    std::cout << "move next" << std::endl;
  }
  return 0;
}
