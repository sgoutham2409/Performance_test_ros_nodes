cmake_minimum_required(VERSION 2.8.3)
project(performance_tests)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  SuperAwesome.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS rospy roscpp std_msgs message_runtime
)

###########
## Build ##
###########
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(cpppub src/pub.cpp)
## Specify libraries to link a library or executable target against
target_link_libraries(cpppub ${catkin_LIBRARIES})

add_executable(cppsub src/sub.cpp)
target_link_libraries(cppsub ${catkin_LIBRARIES})
