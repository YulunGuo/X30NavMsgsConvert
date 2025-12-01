#include "goal_converter/goal_converter.h"
#include <ros/ros.h>

GoalConverter::GoalConverter() : goal_id_counter_(0)
{
    // 订阅geometry_msgs/PoseStamped消息
    pose_subscriber_ = nh_.subscribe("/move_base/goal_pose", 10, &GoalConverter::poseCallback, this);
    
    // 发布MoveBaseActionGoal消息
    goal_publisher_ = nh_.advertise<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 10);
    
    ROS_INFO("Goal Converter Node initialized");
    ROS_INFO("Subscribed to: /move_base/goal_pose [geometry_msgs/PoseStamped]");
    ROS_INFO("Publishing to: /move_base/goal [move_base_msgs/MoveBaseActionGoal]");
}

actionlib_msgs::GoalID GoalConverter::generateGoalID()
{
    actionlib_msgs::GoalID goal_id;
    goal_id.stamp = ros::Time::now();
    
    // 生成唯一的ID：时间戳 + 计数器
    std::stringstream ss;
    ss << "goal_converter_" << goal_id_counter_ << "_" << goal_id.stamp.toNSec();
    goal_id.id = ss.str();
    
    goal_id_counter_++;
    return goal_id;
}

void GoalConverter::poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    ROS_DEBUG("Received PoseStamped message");
    
    // 创建MoveBaseActionGoal消息
    move_base_msgs::MoveBaseActionGoal goal_msg;
    
    // 1. 设置header
    goal_msg.header.stamp = ros::Time::now();
    goal_msg.header.seq = goal_id_counter_;
    goal_msg.header.frame_id = "map";  // 默认为map坐标系
    
    // 2. 设置goal_id
    goal_msg.goal_id = generateGoalID();
    
    // 3. 设置目标位姿（从接收的消息中复制）
    goal_msg.goal.target_pose = *msg;
    
    // 确保目标位姿的时间戳是最新的
    if (goal_msg.goal.target_pose.header.stamp == ros::Time(0)) {
        goal_msg.goal.target_pose.header.stamp = ros::Time::now();
    }
    
    // 发布转换后的消息
    goal_publisher_.publish(goal_msg);
    
    ROS_INFO("Published MoveBaseActionGoal with ID: %s", goal_msg.goal_id.id.c_str());
    ROS_DEBUG("Position: [x: %.2f, y: %.2f, z: %.2f]", 
              goal_msg.goal.target_pose.pose.position.x,
              goal_msg.goal.target_pose.pose.position.y,
              goal_msg.goal.target_pose.pose.position.z);
    ROS_DEBUG("Orientation: [x: %.2f, y: %.2f, z: %.2f, w: %.2f]",
              goal_msg.goal.target_pose.pose.orientation.x,
              goal_msg.goal.target_pose.pose.orientation.y,
              goal_msg.goal.target_pose.pose.orientation.z,
              goal_msg.goal.target_pose.pose.orientation.w);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "goal_converter_node");
    
    GoalConverter converter;
    
    ros::spin();
    
    return 0;
}