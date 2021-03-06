#!/usr/bin/env python

import rospy
from socket import *
import sys
from sensor_msgs.msg import JointState
import json

#settings for the service
host = "192.168.2.6"  # set to IP address of target computer
port = 1212
addr = (host, port)
UDPSock = socket(AF_INET, SOCK_DGRAM)


def callback_pos(data):
    send_message(json.dumps({"shoulder_pan_joint": data.position[0], "shoulder_lift_joint": data.position[1
    ],
                             "elbow_joint": data.position[2], "wrist_1_joint": data.position[3],
                             "wrist_2_joint": data.position[4], "wrist_3_joint": data.position[5]}))

def send_message(data):
    UDPSock.sendto(data, addr)

def listener():
    rospy.init_node('hololens_bridge', anonymous=True)
    rospy.Subscriber("/simulation/joint_states", JointState, callback_pos)

    rospy.spin()

if __name__ == '__main__':
    listener()
