#ifndef TELEOP_FRANKA_JOY_H
#define TELEOP_FRANKA_JOY_H

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/Joy.h>
#include <franka_msgs/FrankaState.h>
#include <ros_falcon/falconForces.h>
#include <map>
#include <string>

// Añade estos includes para los tipos de mensaje de acción
#include <franka_gripper/MoveActionGoal.h>
#include <franka_gripper/GraspActionGoal.h>

namespace teleop_franka_joy
{

class TeleopFrankaJoy
{
public:
  TeleopFrankaJoy(ros::NodeHandle* nh, ros::NodeHandle* nh_param);

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::Subscriber joy_sub_;
  ros::Subscriber franka_state_sub_;
  ros::Publisher cmd_PoseStamped_pub_;
  ros::Publisher gripper_move_pub_;
  ros::Publisher gripper_grasp_pub_;

  franka_msgs::FrankaState current_franka_state_;
  geometry_msgs::PoseStamped equilibrium_pose_;

  // Nuevos
  // Parámetros de ganancia y posición base (desde YAML)
  double base_x_, base_y_, base_z_;
  double Kx_, Ky_, Kz_;

  int control_gripper_button_; // Botón para controlar la pinza


  // Parámetros gripper
  double gripper_width_;
  int    gripper_inc_button_, gripper_dec_button_, gripper_action_button_;
  double gripper_move_speed_;
  double grasp_speed_, grasp_force_, grasp_epsilon_inner_, grasp_epsilon_outer_;


};

}  // namespace teleop_franka_joy

#endif
