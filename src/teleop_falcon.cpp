#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <ros_falcon/falconForces.h>
#include <franka_msgs/FrankaState.h>

class TeleopFalcon
{
public:
  TeleopFalcon(ros::NodeHandle& nh)
    : tf_listener_(tf_buffer_)
  {
    ros::param::param("/teleop_falcon/K", K_, 0.05);
    ros::param::param("/teleop_falcon/threshold", threshold_, 0.5);

    franka_state_sub_ = nh.subscribe("/franka_state_controller/franka_states", 10,
                                     &TeleopFalcon::frankaStateCallback, this);
    falcon_force_pub_ = nh.advertise<ros_falcon::falconForces>("/falconForce", 10);
  }

private:
  ros::Subscriber franka_state_sub_;
  ros::Publisher falcon_force_pub_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;

  double K_;
  double threshold_;

  void frankaStateCallback(const franka_msgs::FrankaState::ConstPtr& msg)
  {
    tf2::Vector3 force_fr3K(K_ * msg->O_F_ext_hat_K[0],
                            K_ * msg->O_F_ext_hat_K[1],
                            K_ * msg->O_F_ext_hat_K[2]);

    geometry_msgs::TransformStamped tf_msg;
    try {
      tf_msg = tf_buffer_.lookupTransform("base_falcon", "base_link", ros::Time(0), ros::Duration(0.1));
    } catch (tf2::TransformException& ex) {
      ROS_WARN_STREAM_THROTTLE(2.0, "TF lookup failed: " << ex.what());
      return;
    }

    tf2::Quaternion q;
    tf2::fromMsg(tf_msg.transform.rotation, q);
    tf2::Matrix3x3 R(q);

    tf2::Vector3 force_transformed = force_fr3K;
    double norm = force_transformed.length();

    ros_falcon::falconForces force_msg;
    if (norm >= threshold_) {
      force_msg.X = force_transformed.x();
      force_msg.Y = force_transformed.y();
      force_msg.Z = force_transformed.z();
    } else {
      force_msg.X = 0.0;
      force_msg.Y = 0.0;
      force_msg.Z = 0.0;
    }

    falcon_force_pub_.publish(force_msg);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_falcon");
  ros::NodeHandle nh;
  TeleopFalcon tf(nh);
  ros::spin();
  return 0;
}
