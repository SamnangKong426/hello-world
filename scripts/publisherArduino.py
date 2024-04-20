#!/usr/bin/env python3

# sudo rfcomm connect /dev/rfcomm0 20:16:04:18:61:60 1
# rosrun rosserial_python serial_node.py _port:=/dev/rfcomm0 _baud:=9600

import rospy
from std_msgs.msg import Int32

nodeName = 'messagepublisher'

topicNameLeftMotor = 'left_motor_velocity'
topicNameRightMotor = 'right_motor_velocity'

rospy.init_node(nodeName, anonymous=True)

publisherLeftMotor = rospy.Publisher(topicNameLeftMotor, Int32, queue_size=5)
publisherRightMotor = rospy.Publisher(topicNameRightMotor, Int32, queue_size=5)

ratePublisher = rospy.rate(1)

leftMotor = 0
rightMotor = 0

while not rospy.is_shutdown():
    rospy.loginfo(leftMotor)
    rospy.loginfo(rightMotor)

    leftMotor = int(input("Enter left motor velocity (0-255): \n"))
    rightMotor = int(input("Enter right motor velocity (0-255): \n"))

    publisherLeftMotor.publish(leftMotor)
    publisherRightMotor.publish(rightMotor)

    ratePublisher.sleep()