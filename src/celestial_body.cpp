#include "mas_solarsystem/celestial_body.h"
#include <stdlib.h>

CelestialBody::CelestialBody()
	: Node("celestial_body_node",
		rclcpp::NodeOptions()
		   .allow_undeclared_parameters(true)
		   .automatically_declare_parameters_from_overrides(true))
{
  //creation du publisher pour publier le marker sur le topic
  publisher_ = this->create_publisher<visualization_msgs::msg::Marker>("marker_topic", 10);

  //création du subscriber 
  // subscriber_ = thsi->create_subcription<celestial_body::msg::MyMsg>(
  //   "/my_other_topic",10, std::bind(&CelestialBody::callback, this, std::placeholders::_1)
  // );

  //Creation d'un message Marker
  marker_msg = std::make_shared<visualization_msgs::msg::Marker>();

  //Configuration du message Marker
  marker_msg -> header.frame_id = "base_link"; // repère ID
  marker_msg -> header.stamp = this -> now();

  marker_msg -> ns = "my_namespace";
  marker_msg -> id = 0; //ID unique du marker
  marker_msg -> type = visualization_msgs::msg::Marker::SPHERE;
  marker_msg -> action = visualization_msgs::msg::Marker::ADD;

   // Position et orientation du marker

  marker_msg -> pose.position.x = 1.0;
  marker_msg -> pose.position.y = 2.0;
  marker_msg -> pose.position.z = 0.0;

  marker_msg -> pose.orientation.x = 0.0;
  marker_msg -> pose.orientation.y = 0.0;
  marker_msg -> pose.orientation.z = 0.0;
  marker_msg -> pose.orientation.w = 1.0;

  // Echelle du marker
  marker_msg -> scale.x = 0.2;
  marker_msg -> scale.y = 0.2;
  marker_msg -> scale.z = 0.2;

  // Couleur du marker
  marker_msg -> color.r = 0.0;
  marker_msg -> color.g = 1.0;
  marker_msg -> color.b = 0.0;
  marker_msg -> color.a = 1.0;

  timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&CelestialBody::publishMyMsg, this));

}

void CelestialBody::callback(const celestial_body::msg::MyMsg: SharedPtr msg){

}

void CelestialBody::publishMyMsg()
{
  marker_msg_ ->header.stamp = this->now();
  publisher_ -> publish(*marker_msg_);
}
