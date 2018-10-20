#!/usr/bin/env python

import rospy
from performance_tests.msg import SuperAwesome

def callback(data):
    rospy.loginfo("Py sub " + data.data)
    
def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("test", SuperAwesome, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
