cmake_minimum_required(VERSION 3.7)
project(project3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp helper.cpp)
add_executable(project3 ${SOURCE_FILES})