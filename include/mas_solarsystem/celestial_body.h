#ifndef __MAS_SOLARSYSTEM__CELESTIAL_BODY_H__
#define __MAS_SOLARSYSTEM__CELESTIAL_BODY_H__

#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker.hpp>

//Pour Publier
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>

class CelestialBody:public rclcpp::Node
{
  public:

    CelestialBody();

    // std::shared_ptr est un template
    // On crée un type de donnée dérivant de tf2_ros
    // Enfin le nom de la variable
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

  private:
    void callback();
};

#endif // __MAS_SOLARSYSTEM__CELESTIAL_BODY_H__
