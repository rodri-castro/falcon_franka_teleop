#include "teleop_franka_joy/teleop_franka_joy.h"
#include <Eigen/Dense>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <algorithm>
#include <ros_falcon/falconForces.h>

namespace teleop_franka_joy
{

TeleopFrankaJoy::TeleopFrankaJoy(ros::NodeHandle* nh, ros::NodeHandle* nh_param)
{

  // Pubs/Subs
  cmd_PoseStamped_pub_ = nh->advertise<geometry_msgs::PoseStamped>("/cartesian_impedance_example_controller/equilibrium_pose", 1, true);
  joy_sub_ = nh->subscribe("/falcon/joystick", 1, &TeleopFrankaJoy::joyCallback, this);

  // // Gripper action topics
  // gripper_move_pub_  = nh->advertise<franka_gripper::MoveActionGoal>("/franka_gripper/move/goal", 1);
  // gripper_grasp_pub_ = nh->advertise<franka_gripper::GraspActionGoal>("/franka_gripper/grasp/goal", 1);


  // Parámetros desde YAML
  // Leer parámetros de posición base y ganancias
  ros::param::param("/teleop_franka/base_x", base_x_, -0.5);
  ros::param::param("/teleop_franka/base_y", base_y_, 0.2);
  ros::param::param("/teleop_franka/base_z", base_z_, 0.5);

  ros::param::param("/teleop_franka/Kx", Kx_, 10.0);
  ros::param::param("/teleop_franka/Ky", Ky_, 10.0);
  ros::param::param("/teleop_franka/Kz", Kz_, 10.0);

  // ros::param::param("/teleop_franka/control_gripper_button", control_gripper_button_, 2);

  // --- Leer parámetros para el gripper ---
  ros::param::param("/teleop_franka/gripper_initial_width", gripper_width_, 0.03);
  ros::param::param("/teleop_franka/gripper_inc_button",    gripper_inc_button_,    0);
  ros::param::param("/teleop_franka/gripper_dec_button",    gripper_dec_button_,    1);
  ros::param::param("/teleop_franka/gripper_action_button", gripper_action_button_, 2);

  ros::param::param("/teleop_franka/gripper_move_speed",    gripper_move_speed_,    0.1);
  ros::param::param("/teleop_franka/grasp_speed",           grasp_speed_,           0.1);
  ros::param::param("/teleop_franka/grasp_force",           grasp_force_,           5.0);
  ros::param::param("/teleop_franka/grasp_epsilon_inner",   grasp_epsilon_inner_,   0.005);
  ros::param::param("/teleop_franka/grasp_epsilon_outer",   grasp_epsilon_outer_,   0.005);

}

void TeleopFrankaJoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy_msg)
{
  ROS_INFO("Teleop_franka_joy: Entra al callback de joy");
  equilibrium_pose_.pose.position.x = base_x_ + Kx_ * joy_msg->axes[2];  // X
  equilibrium_pose_.pose.position.y = base_y_ + Ky_ * joy_msg->axes[0];  // Y
  equilibrium_pose_.pose.position.z = base_z_ + Kz_ * joy_msg->axes[1];  // Z

  equilibrium_pose_.pose.orientation.x = 1.0;
  equilibrium_pose_.pose.orientation.y = 0.0;
  equilibrium_pose_.pose.orientation.z = 0.0;
  equilibrium_pose_.pose.orientation.w = 0.0;

  cmd_PoseStamped_pub_.publish(equilibrium_pose_);


  // // --- Control del gripper ---
  // // Botón 1: aumentar anchura
  // if (joy_msg->buttons[gripper_inc_button_])
  // {
  //   gripper_width_ += 0.01;
  //   ROS_INFO_STREAM("Gripper width -> " << gripper_width_);
  //   franka_gripper::MoveActionGoal m;
  //   m.goal.width = gripper_width_;
  //   m.goal.speed = gripper_move_speed_;
  //   gripper_move_pub_.publish(m);
  // }
  // // Botón 2: disminuir anchura
  // else if (joy_msg->buttons[gripper_dec_button_])
  // {
  //   gripper_width_ = std::max(0.0, gripper_width_ - 0.01);
  //   ROS_INFO_STREAM("Gripper width -> " << gripper_width_);
  //   franka_gripper::MoveActionGoal m;
  //   m.goal.width = gripper_width_;
  //   m.goal.speed = gripper_move_speed_;
  //   gripper_move_pub_.publish(m);
  // }
  // // Botón 3: acción de grasp
  // else if (joy_msg->buttons[gripper_action_button_])
  // {
  //   franka_gripper::GraspActionGoal g;
  //   g.goal.width   = gripper_width_;
  //   g.goal.epsilon.inner = grasp_epsilon_inner_;
  //   g.goal.epsilon.outer = grasp_epsilon_outer_;
  //   g.goal.speed   = grasp_speed_;
  //   g.goal.force   = grasp_force_;
  //   ROS_INFO_STREAM("Grasping with width " << gripper_width_ << ", force " << grasp_force_);
  //   gripper_grasp_pub_.publish(g);
  // }


}

}  // namespace teleop_franka_joy
