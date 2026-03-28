cmake_minimum_required(VERSION 3.5)
project(demo_rviz)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(cmd_publisher src/cmd_publisher.cpp)
ament_target_dependencies(cmd_publisher rclcpp geometry_msgs)

add_executable(robot_node src/robot_node.cpp)
ament_target_dependencies(robot_node rclcpp geometry_msgs)

install(TARGETS
  talker
  cmd_publisher
  robot_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
