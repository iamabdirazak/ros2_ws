#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("talker");
  auto publisher = node->create_publisher<std_msgs::msg::String>("chatter", 10);

  rclcpp::WallRate loop_rate(1);
  while (rclcpp::ok()) {
    auto message = std_msgs::msg::String();
    message.data = "Hello RViz World!";
    RCLCPP_INFO(node->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher->publish(message);
    loop_rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
