cmake_minimum_required(VERSION 3.12)
project(minion_ultrasonic)


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

find_library(WIRINGPI_LIBRARIES NAMES wiringPi REQUIRED)
find_package(Boost COMPONENTS thread chrono REQUIRED)

set(ULTRASONIC_SOURCES
   src/ultrasonic_publisher.cpp
   src/measurement.cpp
)

add_executable(minion_ultrasonic  ${ULTRASONIC_SOURCES})

target_include_directories(minion_ultrasonic PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries (minion_ultrasonic   ${Boost_LIBRARIES} ${WIRINGPI_LIBRARIES})
target_link_libraries(minion_ultrasonic  crypt rt)

ament_target_dependencies(minion_ultrasonic rclcpp std_msgs sensor_msgs)

install(TARGETS
  minion_ultrasonic
  DESTINATION lib/${PROJECT_NAME})


ament_package()
