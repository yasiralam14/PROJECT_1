cmake_minimum_required(VERSION 3.10)

project(hw4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ipb_algorithm STATIC ipb_algorithm.cpp)

target_include_directories(ipb_algorithm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
