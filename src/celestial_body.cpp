#include "mas_solarsystem/celestial_body.h"
#include <stdlib.h>
#include <cmath>
//#include <string>

CelestialBody::CelestialBody()
	: Node("celestial_body_node",
		rclcpp::NodeOptions()
		   .allow_undeclared_parameters(true)
		   .automatically_declare_parameters_from_overrides(true))
{
  
  
  //creation du publisher pour publier le marker sur le topic
  msg_publisher_ = this->create_publisher<visualization_msgs::msg::Marker>("marker_topic", 1);
  tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
  transform_msg_ = std::make_shared<geometry_msgs::msg::TransformStamped>();

  parentframe_id_ = this -> get_parameter("parentframe_id").as_string();
  childframe_id_ = this -> get_parameter("childframe_id").as_string();
  dist_from_parent_ = this -> get_parameter("dist_from_parent").as_double();
  radius_= this -> get_parameter("radius").as_double();
  orbite_ = this -> get_parameter("orbite").as_double();
  color_r_ = this -> get_parameter("color_r").as_double();
  color_b_ = this -> get_parameter("color_b").as_double();
  color_g_ = this -> get_parameter("color_g").as_double();
  orbital_period_ = this -> get_parameter("orbital_period").as_double();

  angular_pos_ = 0.0;

  //création du subscriber 
  // subscriber_ = thsi->create_subcription<celestial_body::msg::MyMsg>(
  //   "/my_other_topic",10, std::bind(&CelestialBody::callback, this, std::placeholders::_1)
  // );

  //Creation d'un message Marker
  marker_msg_ = std::make_shared<visualization_msgs::msg::Marker>();

  //Configuration du message Marker
  marker_msg_ -> header.frame_id = childframe_id_ ;
  marker_msg_ -> header.stamp = this -> now();
  marker_msg_ -> ns = "my_namespace";
  marker_msg_ -> id = 0;
  marker_msg_ -> type = visualization_msgs::msg::Marker::SPHERE;
  marker_msg_ -> action = visualization_msgs::msg::Marker::ADD;

   // Position et orientation du marker

  marker_msg_ -> pose.position.x = 0.0;
  marker_msg_ -> pose.position.y = 0.0;
  marker_msg_ -> pose.position.z = 0.0;

  marker_msg_ -> pose.orientation.x = 0.0;
  marker_msg_ -> pose.orientation.y = 0.0;
  marker_msg_ -> pose.orientation.z = 0.0;
  marker_msg_ -> pose.orientation.w = 1.0;

  // Echelle du marker
  marker_msg_ -> scale.x = 2*radius_;
  marker_msg_ -> scale.y = 2*radius_;
  marker_msg_ -> scale.z = 2*radius_;

  // Couleur du marker
  marker_msg_ -> color.r = color_r_;
  marker_msg_ -> color.g = color_g_;
  marker_msg_ -> color.b = color_b_;
  marker_msg_ -> color.a = 0.5;

  //INitialisation des onformations de transformation
  transform_msg_-> header.frame_id = parentframe_id_ ; //nom repère parent
  transform_msg_-> child_frame_id = childframe_id_ ;  //nom repère enfant
  transform_msg_-> transform.translation.x = dist_from_parent_ ; 
  transform_msg_-> transform.translation.y = 0.0;
  transform_msg_-> transform.translation.z = 0.0;

  transform_msg_-> transform.rotation.x = 0.0;
  transform_msg_-> transform.rotation.y = 0.0;
  transform_msg_-> transform.rotation.z = 1.0;
  transform_msg_-> transform.rotation.w = 1.0;
  

  // Création d'un timer pour publier le Marker et la transformation toutes les 100 ms
  timer_ = this->create_wall_timer( std::chrono::milliseconds(100), std::bind(&CelestialBody::publishTransform, this)
                                  
  );

}

// void CelestialBody::callback(const celestial_body_msgs::msg::MyMsg::SharedPtr msg){

// }


void CelestialBody::publishTransform()
{

  marker_msg_-> header.stamp = this->now();
  
  transform_msg_-> transform.translation.x = cos(angular_pos_) * orbite_;
  transform_msg_-> transform.translation.y = sin(angular_pos_) * orbite_;
 
  angular_pos_ += 2* M_PI/100;
  //ajustement angular s'il dépasse 2PI
  //angular_pos_ = std::fmod(angular_pos_, 2*M_PI); 

  msg_publisher_-> publish(*marker_msg_);
  transform_msg_ -> header.stamp = now();


  tf_broadcaster_-> sendTransform(*transform_msg_);
}
