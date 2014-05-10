project(CameraTest)
cmake_minimum_required(VERSION 2.8)

find_package(PCL 1.7 REQUIRED COMPONENTS)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES})

