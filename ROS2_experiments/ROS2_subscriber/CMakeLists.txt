
cmake_minimum_required(VERSION 3.12)
project(parameter_subscriber)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

include_directories(src)

# 找到ROS 2的必要包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 添加可执行文件
add_executable(param_subscriber src/subscriber.cpp)

# 链接必要的库
ament_target_dependencies(param_subscriber rclcpp std_msgs)

# 安装可执行文件
install(TARGETS
  param_subscriber
  DESTINATION lib/${PROJECT_NAME})

# 必须的ament指令
ament_package()


# if run error please use:
# LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./Project
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
