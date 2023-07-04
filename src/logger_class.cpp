#include "rclcpp/rclcpp.hpp"



// Create a class called LoggerNode which inherits from rclcpp::Node.
// This gives us access to all the members and fuctions of rclcpp::Node.
class LoggerNode : public rclcpp::Node
{
public:
    // Our LoggerNode() constructor derives its base constructore from Node()
    // and passes one parameter that is the name name "my_node_name" in this case.  
    LoggerNode() : Node("my_node_name")
    {
        // this refers to the Node class we are deriving from.
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(200),
            std::bind(&LoggerNode::timerCallback, this));
    }

private:
    void timerCallback()
    {
        RCLCPP_INFO(this->get_logger(), "Hello from ROS2");
    }

    // timer_ is a rclcpp SharedPtr type and is private to the LoggerNode() class.
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LoggerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}