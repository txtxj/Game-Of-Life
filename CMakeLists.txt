cmake_minimum_required(VERSION 3.21)
project(LiveGame)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameOfLife main.cpp)

target_link_libraries(GameOfLife ${OpenCV_LIBRARIES})