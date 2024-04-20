#!/usr/bin/env python3

import rospy 
from geometry_msgs.msg import Twist

import time
import bluetooth

import signal
import sys

##########################################################################################
#Bluetooth parameters

bluetooth_mac = '00:22:11:30:E3:DA'

rospy.init_node('ros_bluetooth_driver',anonymous=True)
orient = Twist()

rospy.loginfo("Staring ROS-Bluetooth Driver node")

##########################################################################################
def speed_send(data):
    pass

##########################################################################################
def reset_robot(data):
    global bluetooth_serial_handle

    send_data = 'r\r'

    rospy.loginfo("Resetting robot")

    try:
        bluetooth_serial_handle.send(str(send_data))
        rospy.sleep(1)
    except:
        rospy.logwarn("Unable to send BL data")
        pass

##########################################################################################
#Publishing and subscribing to topics

rospy.Subscriber('car_robot/cmd_vel', Twist, queue_size=10)

def quit_code(signal,frame):
    
    reset_robot(0)

    rospy.loginfo("Quitting")
    sys.exit(1)

