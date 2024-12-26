
cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(Project main.cpp)

target_link_libraries(Project)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# if run error please use:
# LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./Project
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..