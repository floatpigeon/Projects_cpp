
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

namespace ROS2Subscriber {

class Subscriber : public rclcpp::Node {
public:
    Subscriber() : Node("param_receiver") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "ros_message", 10, [this](std_msgs::msg::String::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), "Received parameter: %s", msg->data.c_str());
            });
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

}  // namespace ROS2Subscriber

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ROS2Subscriber::Subscriber>());
    rclcpp::shutdown();
    return 0;
}