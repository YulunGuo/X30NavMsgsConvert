#!/usr/bin/env python
import rospy
from geometry_msgs.msg import PoseStamped
import time

def publish_test_pose():
    rospy.init_node('test_pose_publisher', anonymous=True)
    pub = rospy.Publisher('/goal_pose_input', PoseStamped, queue_size=10)
    
    time.sleep(2)
    
    pose_msg = PoseStamped()
    
    pose_msg.header.stamp = rospy.Time.now()
    pose_msg.header.frame_id = "map"
    
    pose_msg.pose.position.x = 1.0
    pose_msg.pose.position.y = 10.0
    pose_msg.pose.position.z = 0.0
    
    pose_msg.pose.orientation.x = 0.0
    pose_msg.pose.orientation.y = 0.0
    pose_msg.pose.orientation.z = 0.0
    pose_msg.pose.orientation.w = 1.0
    
    rospy.loginfo("Publishing test pose...")
    pub.publish(pose_msg)
    
    rospy.loginfo("Test pose published successfully!")
    
    rospy.loginfo("Check the converted message on /move_base/goal topic")

if __name__ == '__main__':
    try:
        publish_test_pose()
    except rospy.ROSInterruptException:
        pass