#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int16

nodeName = 'messagesubs'

topicName = 'ultrasonic_distance'

def ultrasonic_distance_cb(message):
    print("Ultrasonic distance: %s" %message.data)

rospy.init_node(nodeName, anonymous=True)

rospy.Subscriber(topicName, Int16, ultrasonic_distance_cb)

rospy.spin()