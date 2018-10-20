#!/usr/bin/env python

import rospy
from performance_tests.msg import SuperAwesome
from std_msgs.msg import Float32

freqpublish = 0

def sender():
    pub = rospy.Publisher('test', SuperAwesome, queue_size=1)
    freqpub = rospy.Publisher('testpubfreq', Float32, queue_size=1);
    rospy.init_node('sender', anonymous=True)
    rospy.Timer(rospy.Duration(5), freqpub_callback)
    frequency = 100
    rate = rospy.Rate(frequency)
    msg = SuperAwesome()
    pubFreq = Float32()
    while not rospy.is_shutdown():
        msg.data = "%s" % rospy.Time.now()
        pubFreq.data = frequency
        pub.publish(msg)
	if freqpublish == 1:
           freqpub.publish(pubFreq)
           print 'pubf = ' + str(pubFreq.data)
        rate.sleep()

def freqpub_callback(event):
    freqpublish = 1
    print 'Timer called at ' + str(event.current_real)
   
if __name__ == '__main__':
    try:
        sender() 
    except rospy.ROSInterruptException:
        pass
