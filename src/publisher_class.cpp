#include "rclcpp/rclcpp.hpp" //Basic ROS library

// #include "std_msgs/msg/string.hpp"

#include "std_msgs/msg/int32.hpp"   //ROS int type messages
std_msgs::msg::Int32 msg_int32;     //create an Int32 object calls msg_int32

#include "sensor_msgs/msg/laser_scan.hpp"   //ROS laser scan messages.
sensor_msgs::msg::LaserScan msg_laserscan;  //create a LaserScan object called msg_laserscan


using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node
{
    public:
    PublisherNode() : Node("publisher_node")
    {
        publisher_ = create_publisher<std_msgs::msg::Int32>("int_topic", 10);
        timer_ = create_wall_timer(
        500ms, std::bind(&PublisherNode::timer_callback, this));
    }

    void timer_callback()
    {
        message_.data += 1;
        publisher_->publish(message_);
    }

    private:
        rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        std_msgs::msg::Int32 message_;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("logger_node");

    rclcpp::Rate loop_rate(10);

    int counter = 0;

    while (rclcpp::ok()) {
        RCLCPP_INFO(node->get_logger(), "Hello %d", counter++);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

}
