#ifndef GODEL_GRINDER_SERVICE_H
#define GODEL_GRINDER_SERVICE_H

#include <ros/ros.h>
#include <godel_msgs/GrinderStationAction.h>
#include <actionlib/server/simple_action_server.h>
#include <std_msgs/UInt16.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <string>
#include <fstream>

namespace godel_grinder
{

    class GodelGrinderService
    {
    public:
        GodelGrinderService(ros::NodeHandle& nh);

        void moveToPosition(std::string p);
        void wait();

        void screw();
        void unscrew();

    private:
        ros::NodeHandle nh_;
        actionlib::SimpleActionServer<godel_msgs::GrinderStationAction> as_;
        moveit::planning_interface::MoveGroupInterface move_group;
        ros::Publisher pub;

        std::ofstream arduino;

        godel_msgs::GrinderStationResult result;
        void exec(const godel_msgs::GrinderStationGoalConstPtr &goal);
    };
}

#endif // GODEL_GRINDER_SERVICE_H
