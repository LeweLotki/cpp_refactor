cmake_minimum_required(VERSION 3.15)
project(stereovision_path_planning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(stereo ${PROJECT_SOURCES})

target_link_libraries(stereo PRIVATE ${OpenCV_LIBS})
target_link_libraries(stereo PRIVATE ${Boost_LIBRARIES})

target_include_directories(stereo PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(stereo PRIVATE ${Boost_INCLUDE_DIRS})

