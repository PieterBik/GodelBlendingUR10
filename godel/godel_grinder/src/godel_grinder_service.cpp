//
// Created by parallels on 1/15/18.
//


#include <godel_grinder/godel_grinder_service.h>
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>


godel_grinder::GodelGrinderService::GodelGrinderService(ros::NodeHandle& nh) : nh_(nh), move_group("manipulator") {


    this->service = nh.advertiseService("change_disks", &GodelGrinderService::changeDisks, this);
    this->pub = nh.advertise<std_msgs::UInt16>("Motor_driver", 1000);
}

bool godel_grinder::GodelGrinderService::changeDisks(godel_msgs::GrinderStation::Request  &req,
          godel_msgs::GrinderStation::Response &res) {

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


    return true;
}

void godel_grinder::GodelGrinderService::moveToPosition(std::string p) {
    move_group.setNamedTarget(p.c_str());
    move_group.move();
}


void godel_grinder::GodelGrinderService::wait() {
    std::this_thread::sleep_for(std::chrono::milliseconds(21000));
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