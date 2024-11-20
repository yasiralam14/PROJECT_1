cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

project(OpenCV)

# Find OpenCV
find_package(OpenCV 4 REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(main main.cpp)

# Link OpenCV libraries
target_link_libraries(main ${OpenCV_LIBS})

