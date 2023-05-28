#include "rclcpp/rclcpp.hpp" //Basic ROS library

// #include "std_msgs/msg/string.hpp"

#include "std_msgs/msg/int32.hpp"   //ROS int type messages
std_msgs::msg::Int32 msg_int32;     //create an Int32 object calls msg_int32

#include "sensor_msgs/msg/laser_scan.hpp"   //ROS laser scan messages.
sensor_msgs::msg::LaserScan msg_laserscan;  //create a LaserScan object called msg_laserscan





int main(int argc, char * argv[]) {

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
