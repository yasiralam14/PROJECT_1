cmake_minimum_required(VERSION 3.10)
project(task_1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(cmake/StaticAnalyzers.cmake)

add_executable(task_1 task1.cpp)