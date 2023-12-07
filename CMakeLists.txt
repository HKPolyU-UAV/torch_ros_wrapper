cmake_minimum_required(VERSION 3.16)
project(torch_ros_wrapper)

add_compile_options(-std=c++17)

set(Torch_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libtorch/share/cmake/Torch/")

find_package(catkin REQUIRED COMPONENTS
  nodelet
  roscpp
  std_msgs
  roslaunch
  geometry_msgs
  mavros_msgs
  cv_bridge
  image_transport
  sensor_msgs
  visualization_msgs
  tf
  rospy
)

catkin_python_setup()

# The Usuals
find_package(OpenCV 4 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Sophus REQUIRED)


# Torch
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

roslaunch_add_file_check(launch)

catkin_package(
  # INCLUDE_DIRS include

  CATKIN_DEPENDS 
  rospy
  geometry_msgs 
  mavros_msgs 
  roscpp
  std_msgs
)

set(Sophus_LIBRARIES libSophus.so)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${Sophus_INCLUDE_DIRS}
)

catkin_install_python(PROGRAMS 
  scripts/ConvertCppPt.py
  
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

############################################################################
## Declare a C++ library

add_library(torch_ros
  src/torch_ros_wrapper.cpp
  src/tools/RosTopicConfigs.cpp
  )

# Specify libraries to link a library or executable target against
target_link_libraries(torch_ros
  ${catkin_LIBRARIES}
  ${OpenCV_INCLUDE_DIRS}
  ${Sophus_INCLUDE_DIRS}
  ${TORCH_LIBRARIES}
)

############################################################################
## Declare C++ executables

add_executable(lala
  src/lala.cpp
)

target_link_libraries(lala
  ${catkin_LIBRARIES}
  ${TORCH_LIBRARIES}
)




  
  





