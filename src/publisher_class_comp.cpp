// This is going to be the composible node version.
// I am using a different file here because I don't know how well this is going to work
// and I don't want to reinvent the wheel at this point but the tutorials I am following
// are based on it and it is supposed to be the new standard.
#include "rclcpp/rclcpp.hpp"

// For std_msgs/msg/Int32
#include "std_msgs/msg/int32.hpp"
std_msgs::msg::Int32 msg_int32;

// For std_msgs/msg/string
#include "std_msgs/msg/string.hpp"


// For sensor_msgs/msg/LaserScan
#include "sensor_msgs/msg/laser_scan.hpp"
sensor_msgs::msg::LaserScan msg_laserscan;



// Create a class called PublisherNode which inherits from rclcpp::Node.
// This gives us access to all the members and fuctions of rclcpp::Node.
class PublisherNode : public rclcpp::Node
{
public:

    // Create a constructure PublisherNode() which calls the base class constructor rclcpp::Node()
    // and gives the node name of "publisher_node" for the ROS graph
    // Not certain why some documentation writes this as PublisherNode() : rclcpp::Node("publisher_node")
    PublisherNode() : Node("publisher_node")
    {
        // Instead of hard-coding everyhthing like a turkey, we are going to setup some parameters.
        // Maybe these should be more global.  Not sure yet.
        // declare_parameter<std::string>("message_data", "Hello World");
        declare_parameter<std::string>("message_data", "Hello World");
        // Below is another way.  Not sure what is the best way yet
        this->declare_parameter("my_str", rclcpp::PARAMETER_STRING);
        
    
        // Here we initialize the publisher_ member with create_publisher method from rclcpp:Node
        // We tell it with the <std_msgs::msg:Int32> template parameter what kind of message with are publsihing
        // give it a topic name 'int_topic' to publish to and a QualityOfService "10" CHECK THIS
        // Why is it not rclcpp::SystemDefaultQos()?
        // publisher_ = create_publisher<std_msgs::msg::Int32>("int_topic", 10);
        publisher_ = create_publisher<std_msgs::msg::Int32>("int_topic", rclcpp::SystemDefaultsQoS());
        RCLCPP_INFO(get_logger(), "Publisher created");





        // create_wall_timer creates a ROS timer which registers a callback with the ROS event system
        // to be called at some regular interval.  this gives us the same behavior as a rate limited loop
        // Here, 'this' refers to PublisherNode() which inherits from rclcpp::Node::create_wall_timer
        // for more info see: https://www.youtube.com/watch?v=W2Qya_aDE6M&list=PL1R5gSylLha0wxbvXIiNeEr12aoO_VX_8&index=2
        // the create_wall_timer function takes in a duration from the std::chrono library,
        // and then a reference to the callback function that will be executing every loop
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(250),
            std::bind(&PublisherNode::timer_callback, this));
        RCLCPP_INFO(get_logger(), "timer_ created for publisher_node");

    }



private:
    
    // I just moved this from the public: section and it might break the missage_.data component.
    // It probably doesn't need to be public since only 'this' class is using this callback.
    void timer_callback()
    {
        message_.data += 1;
        publisher_->publish(message_);
        RCLCPP_INFO(this->get_logger(), "Hello from publisher_class timer_callback function");
    }
    
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    
    // Register a new private member in our class called timer_.  
    // This holds a SharedPtr to a TimerBase object in rclcpp
    // We initialize it above with the this->create_wall_timer() function
    rclcpp::TimerBase::SharedPtr timer_;
    std_msgs::msg::Int32 message_;
};

int main(int argc, char **argv)
{
    // First we call init which will allow the rclcpp library to setup and configure under the hood so to speak
    rclcpp::init(argc, argv);

    // Nextr we create 'node' object.
    // Note the auto type keyword
    // Note also that we use std::make_shared to create a shared pointer.  
    // TODO: ELABORATE ON THIS LATER
    // TODO: I think the right syntax might be: auto node = std::make_shared<rclcpp::Node>("first_node");
    //     Where we call a template rclcpp::Node and name it first_node
    auto node = std::make_shared<PublisherNode>();
    
    // This will run our 'node' continuously forever.
    rclcpp::spin(node);

    // Run untill we receive a shutdown command.
    rclcpp::shutdown();
    return 0;
}