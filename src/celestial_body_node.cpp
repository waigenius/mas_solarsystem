#include "mas_solarsystem/celestial_body.h"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CelestialBody>();

  rclcpp::spin(node);

  rclcpp::shutdown();

  return 0;
}