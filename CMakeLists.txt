cmake_minimum_required(VERSION 3.10)
project(TWISTP-10000)

set(CMAKE_CXX_STANDARD 17)

find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(TWISTP-10000 src/main.cpp)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(TWISTP-10000
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
)
