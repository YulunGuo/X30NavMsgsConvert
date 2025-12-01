解决部分云深处x30机器狗使用内置start_nav.sh时在rviz中无法下发普通导航点/move_base/goal，只能下发直线导航点/move base direct line/goal的问题
由于导航代码闭源，因此无法通过编译源码加入普通导航点，同时原始的消息类型nav_msgs/MoveBaseActionGoal并不存在
因此通过建立一个节点将rviz中/move_base/goal的geometry_msgs/PoseStamped消息类型转换为move_base_msgs/MoveBaseActionGoal消息类型，从而实现变相下发普通导航点的目的

'
cd ~/catkin_ws/src
git clone https://github.com/YulunGuo/X30NavMsgsConvert.git
cd ..
catkin_make
source ./devel/setup.bash
roslaunch goal_converter goal_converter.launch
'

