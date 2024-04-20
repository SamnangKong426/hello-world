#!/usr/bin/env python3

# sudo rfcomm connect /dev/rfcomm0 00:22:11:30:E3:DA 
# rosrun rosserial_python serial_node.py _port:=/dev/rfcomm0 _baud:=9600

import rospy
from geometry_msgs.msg import Twist

nodeName = 'messagepubs'

topicName = 'cmd_vel'

rospy.init_node(nodeName, anonymous=True)

publisher = rospy.Publisher(topicName, Twist, queue_size=10)

ratePublisher = rospy.Rate(1)

v_x = 0
v_y = 0
omega = 0

message = Twist()

while not rospy.is_shutdown():
    rospy.loginfo(v_x)
    rospy.loginfo(v_y)
    rospy.loginfo(omega)

    v_x = float(input("Enter linear velocity (m/s): \n"))
    v_y = float(input("Enter lateral velocity (m/s): \n"))
    omega = float(input("Enter angular velocity (rad/s): \n"))

    message.linear.x = v_x
    message.linear.y = v_y
    message.angular.z = omega

    publisher.publish(message)

    ratePublisher.sleep()
    