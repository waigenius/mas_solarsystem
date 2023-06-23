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
    //void callback(const celestial_body_msgs::msg::MyMsg::SharedPtr msg);
    void publishMarker();

    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr msg_publisher_ ; 
    std::shared_ptr<visualization_msgs::msg::Marker> marker_msg_ ;
    std::shared_ptr<geometry_msgs::msg::TransformStamped> transform_msg_ ;
    rclcpp::TimerBase::SharedPtr timer_;
    double angular_pos_;
    double radius_;

};

#endif // __MAS_SOLARSYSTEM__CELESTIAL_BODY_H__

