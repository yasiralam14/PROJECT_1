cmake_minimum_required(VERSION 3.10)

project(mylibrary)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/results/lib")

add_library(mylibrary STATIC src/subtract.cpp src/sum.cpp)

set_target_properties(mylibrary PROPERTIES OUTPUT_NAME "ipb_arithmetic")

install(TARGETS mylibrary 
ARCHIVE DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/install")   

install(DIRECTORY include/
DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/install/include")