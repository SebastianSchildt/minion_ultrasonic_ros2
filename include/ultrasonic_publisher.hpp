#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/range.hpp"

#include "measurement.hpp"


class UltrasonicPublisher : public rclcpp::Node
{
public:
  UltrasonicPublisher();

private:
  USSMeasurement *sensor;
  uint32_t _trig_pin;
  uint32_t _echo_pin;
  void timer_callback();
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::Range>::SharedPtr publisher_;
};
