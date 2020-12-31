# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.12.1)
project (Ultrasonic)


find_package(Threads REQUIRED)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi REQUIRED)
find_package(Boost COMPONENTS thread chrono REQUIRED)


set(ULTRASONIC_SOURCES
   ../src/main.cpp
   ../src/measurement.cpp
)

add_executable (ultrasonic  ${ULTRASONIC_SOURCES} )
target_link_libraries (ultrasonic PRIVATE Threads::Threads  ${Boost_LIBRARIES} ${WIRINGPI_LIBRARIES})
target_link_libraries(ultrasonic PRIVATE crypt rt)