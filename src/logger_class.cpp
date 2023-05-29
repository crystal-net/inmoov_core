#include "rclcpp/rclcpp.hpp" //Basic ROS library

// #include "std_msgs/msg/string.hpp"

#include "std_msgs/msg/int32.hpp"   //ROS int type messages
std_msgs::msg::Int32 msg_int32;     //create an Int32 object calls msg_int32

#include "sensor_msgs/msg/laser_scan.hpp"   //ROS laser scan messages.
sensor_msgs::msg::LaserScan msg_laserscan;  //create a LaserScan object called msg_laserscan


class LoggerNode : public rclcpp::Node
{
public:
    LoggerNode() : Node("logger_node")
    {
    counter_ = 0;
    timer_ = create_wall_timer(
    500, std::bind(&LoggerNode::timer_callback, this));
    }
    
    void timer_callback()
    {
        RCLCPP_INFO(get_logger(), "Hello %d", counter_++);
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);

    auto node = std::make_shared<LoggerNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
