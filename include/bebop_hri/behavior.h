#include <string>

#include <boost/shared_ptr.hpp>

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>

// This is a placeholder for obzerver
#include <sensor_msgs/RegionOfInterest.h>
#include "cftld_ros/Track.h"

#include "bebop_hri/util.h"
#include "bebop_hri/behavior_tools.h"

namespace bebop_hri
{

namespace constants
{

enum bebop_mode_t
{
  MODE_IDLE = 0,
  MODE_SEARCHING = 1,
  MODE_LONGRANGE_ENGAGING = 2,
  MODE_LONGRANGE_ENGAGED = 3,
  MODE_APPROACHING_PERSON = 4,
  MODE_APPROACHING_LOST = 5,
  MODE_FOLLOWING_PERSON = 6,
  MODE_CLOSERANGE_ENGAGED = 7,
  MODE_MANUAL = 8,
  MODE_NUM
};

const std::string STR_BEBOP_MODE_MAP[MODE_NUM + 1] =
{
  "Idle", "Searching", "Long-range Engaging", "Long-range Engaged",
  "Approaching The person", "Following The Person", "Lost The Person", "Close-range Engaged",
  "Manual (Joy Override)","NAN"
};

#define BEBOP_MODE_STR(x) (::bebop_hri::constants::STR_BEBOP_MODE_MAP[x])

}  // namespace constants



class BebopBehaviorNode
{
protected:
  // ros stuff
  ros::NodeHandle nh_;
  ros::NodeHandle priv_nh_;

  behavior_tools::ASyncSub<sensor_msgs::Joy> sub_joy_;
  behavior_tools::ASyncSub<sensor_msgs::RegionOfInterest> sub_periodic_tracks_;
  behavior_tools::ASyncSub<cftld_ros::Track> sub_visual_tracker_track_;

  // To reset/initialize the visualal tracker
  ros::Publisher pub_cftld_tracker_reset_;
  ros::Publisher pub_cftld_tracker_init_;

  // To enable/disable visual servo
  ros::Publisher pub_visual_servo_enable_;
  ros::Publisher pub_visual_servo_roi_;

  // To enable/disable obzerver
  ros::Publisher pub_obzerver_enable_;

  util::StringPublisher status_publisher_;

  // Messages
  std_msgs::Empty msg_empty_;
  std_msgs::Bool msg_bool_;

  // internal stuff
  constants::bebop_mode_t bebop_mode_;
  constants::bebop_mode_t bebop_prev_mode_;
  constants::bebop_mode_t bebop_resume_mode_;

  ros::Time last_transition_time_;

  // params
  double param_update_rate_;
  int32_t param_init_mode_;
  int32_t param_joy_override_button_;
  double param_idle_timeout_;
  double param_joy_override_timeout_;

  void Reset();
  void UpdateParams();
  void UpdateBehavior();

public:
  BebopBehaviorNode(ros::NodeHandle& nh, ros::NodeHandle &priv_nh);
  void Spin();

};

}  // namespace bebop_hri