cmake_minimum_required(VERSION 3.15)
project(your_project_name)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)

add_executable(your_executable_name src/main.cpp)

target_link_libraries(your_executable_name PRIVATE opencv::opencv ${OpenCV_LIBS})

