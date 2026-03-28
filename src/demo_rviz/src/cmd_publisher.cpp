#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class CmdPublisher : public rclcpp::Node
{
public:
    CmdPublisher() : Node("cmd_publisher")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&CmdPublisher::publish_command, this));
    }

private:
    void publish_command()
    {
        auto msg = geometry_msgs::msg::Twist();

        msg.linear.x = 0.5;
        msg.angular.z = 0.5;

        publisher_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "Publishing velocity command");
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CmdPublisher>());
    rclcpp::shutdown();
    return 0;
}
