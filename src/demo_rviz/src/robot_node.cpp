#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose.hpp"

class RobotNode : public rclcpp::Node
{
public:
    RobotNode() : Node("robot_node")
    {
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel", 10,
            std::bind(&RobotNode::cmd_callback, this, std::placeholders::_1));

        publisher_ = this->create_publisher<geometry_msgs::msg::Pose>("/robot_pose", 10);

        x_ = 0.0;
        y_ = 0.0;
        theta_ = 0.0;

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&RobotNode::update_position, this));
    }

private:
    void cmd_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        linear_velocity_ = msg->linear.x;
        angular_velocity_ = msg->angular.z;
    }

    void update_position()
    {
        theta_ += angular_velocity_ * 0.1;
        x_ += linear_velocity_ * cos(theta_) * 0.1;
        y_ += linear_velocity_ * sin(theta_) * 0.1;

        auto pose = geometry_msgs::msg::Pose();
        pose.position.x = x_;
        pose.position.y = y_;

        publisher_->publish(pose);
    }

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Pose>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    double x_, y_, theta_;
    double linear_velocity_, angular_velocity_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotNode>());
    rclcpp::shutdown();
    return 0;
}
