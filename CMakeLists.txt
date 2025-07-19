cmake_minimum_required(VERSION 3.10)
project(twi-launcher)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(twi-launcher src/main.cpp)
target_link_libraries(twi-launcher SDL2 SDL2_mixer GL GLEW)
