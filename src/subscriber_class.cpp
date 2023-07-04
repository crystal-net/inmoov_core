#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"



// For more information see:
// https://www.youtube.com/watch?v=nEonCfJ6Gcc&list=PL1R5gSylLha0wxbvXIiNeEr12aoO_VX_8&index=3


using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber() : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<std_msgs::msg::Int32>(
      "int_topic",
      rclcpp::SystemDefaultsQoS(),
      std::bind(&MinimalSubscriber::topic_callback, this, std::placeholders::_1));
    }


  private:
    void topic_callback(const std_msgs::msg::Int32 & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%d'", msg.data);
    }
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}