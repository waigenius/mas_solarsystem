#include "mas_solarsystem/celestial_body.h"
#include <stdlib.h>
#include <math.h>

CelestialBody::CelestialBody()
	: Node("celestial_body_node",
    radius_ = this -> get_parameter("radius").as_double(),
		rclcpp::NodeOptions()
		   .allow_undeclared_parameters(true)
		   .automatically_declare_parameters_from_overrides(true),
           
       )
{
  //creation du publisher pour publier le marker sur le topic
  msg_publisher_ = this->create_publisher<visualization_msgs::msg::Marker>("marker_topic", 1);
  tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this) ;
  transform_msg_ = std::shared_ptr<geometry_msgs::msg::TransformStamped>(this);

  //Angular alpha pour 
  angular_pos_ = 0.0;

  //création du subscriber 
  // subscriber_ = thsi->create_subcription<celestial_body::msg::MyMsg>(
  //   "/my_other_topic",10, std::bind(&CelestialBody::callback, this, std::placeholders::_1)
  // );

  //Creation d'un message Marker
  marker_msg_ = std::make_shared<visualization_msgs::msg::Marker>();

  //Configuration du message Marker
  marker_msg_ -> header.frame_id = "base_link"; // repère ID


  marker_msg_ -> header.stamp = this -> now();

  marker_msg_ -> ns = "my_namespace";
  marker_msg_ -> id = 0; //ID unique du marker
  marker_msg_ -> type = visualization_msgs::msg::Marker::SPHERE;
  marker_msg_ -> action = visualization_msgs::msg::Marker::ADD;

   // Position et orientation du marker

  marker_msg_ -> pose.position.x = 1.0;
  marker_msg_ -> pose.position.y = 0.0;
  marker_msg_ -> pose.position.z = 0.0;

  marker_msg_ -> pose.orientation.x = 0.0;
  marker_msg_ -> pose.orientation.y = 0.0;
  marker_msg_ -> pose.orientation.z = 0.0;
  marker_msg_ -> pose.orientation.w = 1.0;

  // Echelle du marker
  marker_msg_ -> scale.x = 1.0;
  marker_msg_ -> scale.y = 1.0;
  marker_msg_ -> scale.z = 1.0;

  // Couleur du marker
  marker_msg_ -> color.r = 1.0;
  marker_msg_ -> color.g = 1.0;
  marker_msg_ -> color.b = 0.0;
  marker_msg_ -> color.a = 0.5;

  timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&CelestialBody::publishMarker, this));

}

// void CelestialBody::callback(const celestial_body_msgs::msg::MyMsg::SharedPtr msg){

// }


void CelestialBody::publishMarker()
{
  marker_msg_-> header.stamp = this->now();
  // Changer la pos X et Y et la rotation sur elle même (ANimation)
  
  marker_msg_-> pose.position.x = cos(angular_pos_) * radius_;
  marker_msg_-> pose.position.y = sin(angular_pos_) * radius_;

  // attribut

  msg_publisher_-> publish(*marker_msg_);
}
