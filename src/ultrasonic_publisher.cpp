// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/range.hpp"

#include "measurement.hpp"


using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minion_ultrasonic"), count_(0)
  {
    publisher_ = this->create_publisher<sensor_msgs::msg::Range>("ultrasonic_range", 10);
    sensor=new USSMeasurement(31,30);
    //sensor=new USSMeasurement(_trig_pin,_echo_pin);
    timer_ = this->create_wall_timer(
      200ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  USSMeasurement *sensor;
  uint32_t _trig_pin=31;
  uint32_t _echo_pin=30;
  void timer_callback()
  {
    auto msg = sensor_msgs::msg::Range();
    msg.radiation_type=msg.ULTRASOUND;
    msg.field_of_view=0;
    msg.min_range=0.0;
    msg.max_range=1.0;
    msg.range=sensor->getDistance();
    if (msg.range == -1.0) {//no detection {
      msg.range = std::numeric_limits<float>::infinity();
    }
    RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", msg.range);
    publisher_->publish(msg);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::Range>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
