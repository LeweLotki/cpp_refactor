cmake_minimum_required(VERSION 3.15)
project(your_project_name)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find the OpenCV package
find_package(OpenCV REQUIRED)

# Print OpenCV version (optional, for debugging purposes)
message(STATUS "Using OpenCV version ${OpenCV_VERSION}")

# Automatically add all .cpp files in the src directory to the project
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(your_executable_name ${PROJECT_SOURCES})

# Link your executable with the OpenCV libraries
target_link_libraries(your_executable_name PRIVATE ${OpenCV_LIBS})

# If you need to include directories for OpenCV headers (usually not necessary as find_package handles it)
target_include_directories(your_executable_name PRIVATE ${OpenCV_INCLUDE_DIRS})

