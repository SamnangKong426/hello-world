#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import Twist
import sys

def move_robot(lin_vel_x, lin_vel_y, ang_vel):
    rospy.init_node('move_robot', anonymous=False)

    pub = rospy.Publisher('car_robot/cmd_vel', Twist, queue_size=10)
    rate = rospy.Rate(10)

    vel = Twist()

    while not rospy.is_shutdown():

        vel.linear.x = lin_vel_x
        vel.linear.y = lin_vel_y
        vel.linear.z = 0

        vel.angular.x = 0
        vel.angular.y = 0
        vel.angular.z = ang_vel

        rospy.loginfo("Linear Vel_x = %f: Vel_y = %f: Angular Vel = %f", lin_vel_x, lin_vel_y, ang_vel)

        pub.publish(vel)

        rate.sleep()

if __name__ == '__main__':
    try: 
        move_robot(float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3]))
    except rospy.ROSInterruptException:
        pass