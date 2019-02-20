cmake_minimum_required(VERSION 2.8.3)
project(roombot_driver)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(roombot_joy_to_twist src/roombot_joy_to_twist.cpp)
target_link_libraries(roombot_joy_to_twist ${catkin_LIBRARIES})

add_executable(roombot_twist_to_tf src/roombot_twist_to_tf.cpp)
target_link_libraries(roombot_twist_to_tf ${catkin_LIBRARIES})

add_executable(twist_marker_visualizer src/twist_marker_visualizer.cpp)
target_link_libraries(twist_marker_visualizer ${catkin_LIBRARIES})

