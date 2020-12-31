from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="minion_ultrasonic",
            executable="minion_ultrasonic",
            name="yahboom_ultrasonic",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"trigger_pin": 31},
                {"echo_pin": 30},
            ]
        )
    ])