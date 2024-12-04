cmake_minimum_required(VERSION 3.30)
project(pong)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add executable
add_executable(${PROJECT_NAME} main.cpp
        game.h
        game.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "Pong")

# Link SDL2
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
