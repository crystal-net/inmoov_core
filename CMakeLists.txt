cmake_minimum_required(VERSION 3.8)
project(inmoov_core)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
# find_package(node REQUIRED)

set (dependencies rclcpp std_msgs sensor_msgs)

add_executable(simple src/simple.cpp)
add_executable(logger src/logger.cpp)
add_executable(logger_class src/logger_class.cpp)
add_executable(publisher_class src/publisher_class.cpp)
add_executable(subscriber_class src/subscriber_class.cpp)
add_executable(system src/system.cpp)

# ament_target_dependencies(logger rclcpp std_msgs)

ament_target_dependencies(simple ${dependencies})
ament_target_dependencies(logger ${dependencies})
ament_target_dependencies(logger_class ${dependencies})
ament_target_dependencies(publisher_class ${dependencies})
ament_target_dependencies(subscriber_class ${dependencies})
ament_target_dependencies(system ${dependencies})

# export information to downstream packages
ament_export_dependencies(
  # rosidl_default_runtime 
  rclcpp 
  sensor_msgs
  # node
  # geometry_msgs
)

install(TARGETS
  simple
  logger
  logger_class
  publisher_class
  subscriber_class
  system
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
