#ifndef GODEL_GRINDER_SERVICE_H
#define GODEL_GRINDER_SERVICE_H

#include <ros/ros.h>
#include <godel_msgs/GrinderStation.h>
#include <std_msgs/UInt16.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <string>

namespace godel_grinder
{

    class GodelGrinderService
    {
    public:
        GodelGrinderService(ros::NodeHandle& nh);

        bool changeDisks(godel_msgs::GrinderStation::Request  &req,
                         godel_msgs::GrinderStation::Response &res);

        void moveToPosition(std::string p);
        void wait();

        void screw();
        void unscrew();

    private:
        ros::NodeHandle nh_;
        ros::ServiceServer service;
        moveit::planning_interface::MoveGroupInterface move_group;
        ros::Publisher pub;
    };
}

#endif // GODEL_GRINDER_SERVICE_H
