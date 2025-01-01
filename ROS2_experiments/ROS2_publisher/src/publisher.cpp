
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

namespace ROS2Publisher {

class Publisher : public rclcpp::Node {
public:
    Publisher() : Node("publisher") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("ros_message", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(1), std::bind(&Publisher::publish_message, this));

        RCLCPP_INFO(this->get_logger(), "SimplePublisherNode started.");
    }

private:
    void publish_message() {
        auto message = std_msgs::msg::String();

        count++;
        message_double = 10 * (sin(count / 1000.0 * std::numbers::pi) + 1);
        buffer         = std::to_string(message_double);
        message.data   = buffer;
        publisher_->publish(message);

        RCLCPP_INFO(this->get_logger(), "Published: %s", message.data.data());
    }

    double count = 0;
    double message_double;
    std::string buffer;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};
}  // namespace ROS2Publisher

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    ROS2Publisher::Publisher publisher;

    rclcpp::spin(std::make_shared<ROS2Publisher::Publisher>());

    rclcpp::shutdown();
    return 0;
}
