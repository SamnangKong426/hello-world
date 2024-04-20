#!/usr/bin/env python3

import rospy
from std_msgs.msg import Int32

nodeName = 'messagesubs'

topicNameLeftEncoder='left_encoder_pulses'
topicNameRightEncoder='right_encoder_pulses'

def callBackFunctionLeftEncoder(message1):
    print("Left encoder pulses: %s" %message1.data)

def callBackFunctionRightEncoder(message2):
    print("Right encoder pulses: %s" %message2.data)

rospy.init_node(nodeName, anonymous=True)

rospy.Subscriber(topicNameLeftEncoder, Int32, callBackFunctionLeftEncoder)
rospy.Subscriber(topicNameRightEncoder, Int32, callBackFunctionRightEncoder)

rospy.spin()
