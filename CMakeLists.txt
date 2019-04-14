cmake_minimum_required(VERSION 2.8.3)
project(ros_answers)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    fiducial_msgs
    tf2
    tf2_ros
    geometry_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

catkin_package()

add_executable(static_tf_example src/static_tf_example.cpp)
target_link_libraries(static_tf_example ${catkin_LIBRARIES})
