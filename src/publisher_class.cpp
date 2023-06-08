#include "rclcpp/rclcpp.hpp"

// For std_msgs/msg/Int32
#include "std_msgs/msg/int32.hpp"
std_msgs::msg::Int32 msg_int32;
// For sensor_msgs/msg/LaserScan
#include "sensor_msgs/msg/laser_scan.hpp"
sensor_msgs::msg::LaserScan msg_laserscan;


class PublisherNode : public rclcpp::Node
{
public:
    PublisherNode() : Node("publisher_node")
    {
        publisher_ = create_publisher<std_msgs::msg::Int32>("int_topic", 10);

        
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(20),
            std::bind(&PublisherNode::timer_callback, this));
    }

    void timer_callback()
    {
        message_.data += 1;
        publisher_->publish(message_);
        RCLCPP_INFO(this->get_logger(), "Hello from publisher_class");
    }

private:
    // void timerCallback()
    // {
    //     RCLCPP_INFO(this->get_logger(), "Hello from publisher_class");
    // }
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std_msgs::msg::Int32 message_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}