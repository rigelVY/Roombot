#!/usr/bin/env python

#reference  (https://github.com/martinschaef/roomba)

import create
import time
import rospy
from std_msgs.msg import Empty
from geometry_msgs.msg import Twist

ROOMBA_PORT="/dev/ttyUSB0"
robot = create.Create(ROOMBA_PORT)
robot.printSensors() # debug output
wall_fun = robot.senseFunc(create.WALL_SIGNAL) # get a callback for a sensor.
print (wall_fun()) # print a sensor value.
robot.toSafeMode()

#send 'go' command to Roomba
def callback_go(msg):
    #rospy.loginfo("Received a /cmd_roomba_vel message!")
    #rospy.loginfo("Linear: [%f %f %f]" % (msg.linear.x, msg.linear.y, msg.linear.z))
    #rospy.loginfo("Angular: [%f %f %f]" % (msg.angular.x, msg.angular.y, msg.angular.z))
    cmpsec = int(msg.linear.x)
    degpsec = int(msg.angular.z)
    robot.go(cmpsec, degpsec)
    time.sleep(0.1)

#send 'stop' command to Roomba
def callback_close():
    robot.close()

def roomba_driver():
    rospy.init_node('roomba_driver')
    rospy.Subscriber("/cmd_roomba_vel", Twist, callback_go)
    rospy.Subscriber("/cmd_roomba_close", Empty, callback_close)
    rospy.spin()

if __name__ == '__main__':
    roomba_driver()
