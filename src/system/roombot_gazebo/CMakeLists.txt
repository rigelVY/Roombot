cmake_minimum_required(VERSION 2.8.3)
project(roombot_gazebo)

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

add_executable(gazebo_model_states_to_tf src/gazebo_model_states_to_tf.cpp)
target_link_libraries(gazebo_model_states_to_tf ${catkin_LIBRARIES})
