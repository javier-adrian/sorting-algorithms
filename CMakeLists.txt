cmake_minimum_required(VERSION 3.28)
project(SA)

find_package(raylib 4.0 REQUIRED)
set(CMAKE_CXX_STANDARD 26)

add_executable(SA main.cpp)

target_link_libraries(${PROJECT_NAME} raylib)