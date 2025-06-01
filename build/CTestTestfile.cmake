# CMake generated Testfile for 
# Source directory: /home/rodri/workspace/rafi_ws/src/joy_franka_control
# Build directory: /home/rodri/workspace/rafi_ws/src/joy_franka_control/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_joy_franka_control_roslaunch-check_launch_teleop_franka.launch "/home/rodri/workspace/rafi_ws/src/joy_franka_control/build/catkin_generated/env_cached.sh" "/usr/bin/python3" "/opt/ros/noetic/share/catkin/cmake/test/run_tests.py" "/home/rodri/workspace/rafi_ws/src/joy_franka_control/build/test_results/joy_franka_control/roslaunch-check_launch_teleop_franka.launch.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/rodri/workspace/rafi_ws/src/joy_franka_control/build/test_results/joy_franka_control" "/opt/ros/noetic/share/roslaunch/cmake/../scripts/roslaunch-check -o \"/home/rodri/workspace/rafi_ws/src/joy_franka_control/build/test_results/joy_franka_control/roslaunch-check_launch_teleop_franka.launch.xml\" \"/home/rodri/workspace/rafi_ws/src/joy_franka_control/launch/teleop_franka.launch\" ")
set_tests_properties(_ctest_joy_franka_control_roslaunch-check_launch_teleop_franka.launch PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/noetic/share/catkin/cmake/test/tests.cmake;160;add_test;/opt/ros/noetic/share/roslaunch/cmake/roslaunch-extras.cmake;66;catkin_run_tests_target;/home/rodri/workspace/rafi_ws/src/joy_franka_control/CMakeLists.txt;60;roslaunch_add_file_check;/home/rodri/workspace/rafi_ws/src/joy_franka_control/CMakeLists.txt;0;")
subdirs("gtest")
