//
// Created by parallels on 1/15/18.
//

#include <godel_grinder/godel_grinder_service.h>
#include <ros/ros.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "godel_grinder_service_node");
    ros::AsyncSpinner asymc_spinner(1);
    ros::NodeHandle nh;

    godel_grinder::GodelGrinderService s(nh);

    ros::spin();
    return 0;
}
