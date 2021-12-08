#include "ros/ros.h"
#include "glass_bridge/glass_bridge.h"
#include <cstdlib>
#include <ctime>

std::string true_path = "";
std::string your_path = "";
int steps_count = 0;

bool add(glass_bridge::glass_bridge::Request &req,glass_bridge::glass_bridge::Response &res)
{
  steps_count++;
  your_path += req.input;
  if (true_path.substr(0, steps_count) != your_path)
    ros::shutdown();

  else
    res.output = your_path;
  ROS_INFO_STREAM("request:" << req.input);
  ROS_INFO_STREAM("sending back response:" << res.output);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "glass_bridge_server");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("glass_bridge", add);
  
  
  srand(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < 18; i++)
  {
    std::string b;
    if (rand() % 2 == 0)
      b = "l";
    else
      b = "r";
    true_path += b;
  }
  
  ROS_INFO_STREAM(true_path);
  
  ROS_INFO_STREAM("READY TO WORK");
  ros::spin();
  return 0;
}
