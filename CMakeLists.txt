cmake_minimum_required(VERSION 3.12)
project(minion_ultrsonic)


# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(common_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(minion_ultrsonic src/publisher_member_function.cpp)
ament_target_dependencies(minion_ultrsonic rclcpp std_msgs sensor_msgs)

install(TARGETS
  minion_ultrsonic
  DESTINATION lib/${PROJECT_NAME})


ament_package()
