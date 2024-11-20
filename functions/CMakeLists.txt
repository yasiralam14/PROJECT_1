cmake_minimum_required(VERSION 3.10)

project(html_writer LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(html_writer STATIC html_writer.cpp)

add_library(image_browser STATIC image_browser.cpp html_writer.cpp)

target_include_directories(html_writer PUBLIC ${PROJECT_SOURCE_DIR}/api)