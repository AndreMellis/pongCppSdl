cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(pong VERSION 1.0)

include_directories("bin/headers" "bin/sources")

#link sdl2 libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

set(SOURCES bin/sources/WindowRendering.cpp bin/sources/Paddle.cpp bin/sources/Dot.cpp bin/sources/Scoring.cpp bin/sources/Colliders.cpp)

add_executable(pong.out main.cpp ${SOURCES})
target_link_libraries(pong.out SDL2::SDL2 SDL2_image SDL2_ttf)
