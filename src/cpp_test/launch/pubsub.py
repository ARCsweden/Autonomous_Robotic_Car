from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cpp_test', # Name of the package the executable is in
            namespace='arc', # Name of the ros2 namespace the node/topics will run in
            executable='talker', # Name of the executable to run (see CMakeLists.txt)
            name='publisher' # Name of the node (can be different from the executable name)
        ),
        Node(
            package='cpp_test',
            namespace='arc',
            executable='listener',
            name='subscriber'
        ),
    ])
