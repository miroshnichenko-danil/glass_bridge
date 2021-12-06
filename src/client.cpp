#include "ros/ros.h"
#include "my_service/glass_bridge.h"
#include <iostream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "glass_bridge_publisher");

  ros::NodeHandle n;
  ros::ServiceClient client=n.serviceClient<my_service::glass_bridge>("glass_bridge");
  my_service::glass_bridge srv;

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
    if (srv.response.output.length() == 17)
    {
      std::cout << "Congratulations, you won";
      return 0;
    }
    if (client.call(srv))
    {
      std::cout << "your path:" << srv.response.output << std::endl;
      std::cout << "move next" << std::endl;
    }
    else
    {
      std::cout << "dead" << std::endl;
      return 0;
    }
  }

  return 0;
}
