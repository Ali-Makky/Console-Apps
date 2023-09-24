cmake_minimum_required(VERSION 3.22)
project(Rock-Paper-Scissor)
add_executable(rock-paper-scissor main.cpp src/lib.cpp)

target_include_directories(rock-paper-scissor PUBLIC include/)