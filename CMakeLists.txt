cmake_minimum_required(VERSION 3.0.2)
project(falcon_franka_teleop)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  roslaunch
  franka_msgs
  ros_falcon
  tf2_ros
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs franka_msgs ros_falcon tf2_ros
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/teleop_franka_joy
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(falcon_franka_teleop_node src/teleop_franka_node.cpp)
add_executable(teleop_falcon src/teleop_falcon.cpp)

target_link_libraries(falcon_franka_teleop_node ${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(teleop_falcon ${catkin_LIBRARIES})

set_target_properties(falcon_franka_teleop_node PROPERTIES OUTPUT_NAME falcon_franka_teleop_node PREFIX "")
set_target_properties(teleop_falcon PROPERTIES OUTPUT_NAME teleop_falcon PREFIX "")

add_dependencies(falcon_franka_teleop_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(teleop_falcon ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


install(TARGETS
  ${PROJECT_NAME}
  falcon_franka_teleop_node
  teleop_falcon
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

if (CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch/teleop_franka.launch)

  find_package(rostest REQUIRED)
  include_directories(include ${catkin_INCLUDE_DIRS})
endif()
