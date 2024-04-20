#!/usr/bin/env python3

import rospy
import bluetooth
from std_msgs.msg import String

def bluetooth_communication():
    rospy.init_node('bluetooth_communication', anonymous=True)
    pub = rospy.Publisher('bluetooth_data_to_arduino', String, queue_size=10)
    rospy.Subscriber('bluetooth_data_from_arduino', String, bluetooth_callback)
    rate = rospy.Rate(10)  # 10hz
    
    addr = '00:22:11:30:E3:DA'  # Replace with the MAC address of your HC-05 module
    port = 1

    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((addr, port))

    while not rospy.is_shutdown():
        # Publish data to Arduino
        data_to_arduino = "Hello from ROS"
        pub.publish(data_to_arduino)
        rospy.loginfo("Sent to Arduino: %s", data_to_arduino)

        # Receive data from Arduino
        data_from_arduino = sock.recv(1024)
        rospy.loginfo("Received from Arduino: %s", data_from_arduino)

        rate.sleep()

    sock.close()

def bluetooth_callback(data):
    # Process data received from Arduino
    rospy.loginfo("Received from ROS: %s", data.data)

if __name__ == '__main__':
    try:
        bluetooth_communication()
    except rospy.ROSInterruptException:
        pass
