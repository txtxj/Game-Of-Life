cmake_minimum_required(VERSION 3.21)
project(LiveGame)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(LiveGame main.cpp)

target_link_libraries(LiveGame ${OpenCV_LIBRARIES})