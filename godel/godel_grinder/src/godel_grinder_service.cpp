//
// Created by parallels on 1/15/18.
//


#include <godel_grinder/godel_grinder_service.h>
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>


godel_grinder::GodelGrinderService::GodelGrinderService(ros::NodeHandle& nh) : nh_(nh), move_group("manipulator"),
                                                                               as_(nh, "change_disks",
                                                                                   boost::bind(&GodelGrinderService::exec, this, _1),
                                                                                   false) {


    this->as_.start();
    this->pub = nh.advertise<std_msgs::UInt16>("Motor_driver", 1000);
}

void godel_grinder::GodelGrinderService::exec(const godel_msgs::GrinderStationGoalConstPtr &goal) {

    ROS_ERROR("STARTING GRINDER CHANGE");
    //step 1: remove nut
    moveToPosition("moveToScrewStation");
    unscrew();
    wait();

    //step 2: remove the disk
    moveToPosition("moveToRemoveDisk");

    //step 3: acquire a disk
    moveToPosition("moveToDiskChange");

    //step 4: acquire nut
    moveToPosition("moveToScrewStation");
    screw();
    wait();

    this->result.sequence = true;
    this->as_.setSucceeded(this->result);
}

void godel_grinder::GodelGrinderService::moveToPosition(std::string p) {
    move_group.setNamedTarget(p.c_str());
    move_group.move();
}


void godel_grinder::GodelGrinderService::wait() {
    ros::Duration(21).sleep();
}

void godel_grinder::GodelGrinderService::screw() {
    std_msgs::UInt16 msg;
    msg.data = 0;

    this->pub.publish(msg);
}

void godel_grinder::GodelGrinderService::unscrew() {
    std_msgs::UInt16 msg;
    msg.data = 1;

    this->pub.publish(msg);
}