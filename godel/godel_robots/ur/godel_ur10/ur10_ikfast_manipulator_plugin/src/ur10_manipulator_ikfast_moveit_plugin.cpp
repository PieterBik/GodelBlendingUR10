#include <ur10_ikfast_manipulator_plugin/ur10_manipulator_ikfast_moveit_plugin.h>
// register IKFastKinematicsPlugin as a KinematicsBase implementation
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(ur10_ikfast_manipulator_plugin::IKFastKinematicsPlugin, kinematics::KinematicsBase);
