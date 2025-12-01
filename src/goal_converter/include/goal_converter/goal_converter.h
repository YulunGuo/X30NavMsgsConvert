#ifndef GOAL_CONVERTER_H
#define GOAL_CONVERTER_H

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <actionlib_msgs/GoalID.h>

class GoalConverter
{
public:
    GoalConverter();
    
private:
    ros::NodeHandle nh_;
    ros::Subscriber pose_subscriber_;
    ros::Publisher goal_publisher_;
    
    // 目标ID计数器
    int goal_id_counter_;
    
    void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    
    // 生成唯一的goal_id
    actionlib_msgs::GoalID generateGoalID();
};

#endif // GOAL_CONVERTER_H