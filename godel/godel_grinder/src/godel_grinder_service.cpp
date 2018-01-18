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

    // HOME
    moveToPosition("disk_swap_home");

    //step 1: remove nut
    moveToPosition("underneath_mounter");
    this->move_group.setMaxVelocityScalingFactor(0.01);
    moveToPosition("on_mounter");
    unscrew();
    moveToPosition("underneath_mounter");
    this->move_group.setMaxVelocityScalingFactor(1.0);
    moveToPosition("disk_swap_home");

    //step 2: remove the disk
    moveToPosition("drop_disk");
    moveToPosition("disk_swap_home");



    //step 3: acquire a disk
    moveToPosition("below_disk");
    ->move_group.setMaxVelocityScalingFactor(0.25);
    moveToPosition("mid_disk");
    this->move_group.setMaxVelocityScalingFactor(0.01);
    moveToPosition("high_disk");
    this->move_group.setMaxVelocityScalingFactor(0.5);
    moveToPosition("away_disk");
    this->move_group.setMaxVelocityScalingFactor(1.0);
    moveToPosition("disk_swap_home");





    //step 4: tighten nut
    moveToPosition("underneath_mounter");
    this->move_group.setMaxVelocityScalingFactor(0.01);
    moveToPosition("on_mounter");
    this->move_group.setMaxVelocityScalingFactor(1.0);
    screw();
    //wait();
    moveToPosition("underneath_mounter");
    moveToPosition("disk_swap_home");

    /*
    //step 2: remove the disk
    moveToPosition("moveToRemoveDisk");


    moveToPosition("moveToDiskChange");

    //step 4: acquire nut
    moveToPosition("moveToScrewStation");
    screw();
    wait(); */

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

    ROS_ERROR("Connecting to grinder on: /dev/grinder_switch_arduino");
    arduino.open("/dev/grinder_switch_arduino",  std::ios_base::out | std::ios_base::in);
    sleep(2.5);
    if(arduino.is_open()) {
        ROS_ERROR("Turning on solonoid");
        arduino << 3 << std::endl;
        sleep(0.5);
    } else {
        ROS_ERROR("Cannot connect to grinder");
    }

    std_msgs::UInt16 msg;
    msg.data = 1;

    this->pub.publish(msg);
    wait();

    if(arduino.is_open()) {
        ROS_ERROR("Turning solonoid off");
        arduino << 2 << std::endl;
        ROS_ERROR("Closing connection");
        arduino.close();
    }
}

void godel_grinder::GodelGrinderService::unscrew() {

    ROS_ERROR("Connecting to grinder on: /dev/grinder_switch_arduino");
    arduino.open("/dev/grinder_switch_arduino",  std::ios_base::out | std::ios_base::in);
    sleep(2.5);
    if(arduino.is_open()) {
        ROS_ERROR("Turning on solonoid");
        arduino << 3 << std::endl;
        sleep(0.5);
    } else {
        ROS_ERROR("Cannot connect to grinder");
    }

    std_msgs::UInt16 msg;
    msg.data = 0;

    this->pub.publish(msg);
    wait();

    if(arduino.is_open()) {
        ROS_ERROR("Turning solonoid off");
        arduino << 2 << std::endl;
        ROS_ERROR("Closing connection");
        arduino.close();
    }
}