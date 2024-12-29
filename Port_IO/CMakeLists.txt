
cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(tcp_server src/server.cpp)
add_executable(tcp_client src/client.cpp)

target_link_libraries(tcp_server pthread)
target_link_libraries(tcp_client pthread)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# if run error please use:
# LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./Project
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..