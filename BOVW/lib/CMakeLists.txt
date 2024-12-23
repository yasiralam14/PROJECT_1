cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Specify the include directories for OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the library
add_library(MyLibrary src/dictionary.cpp src/SearchEngine.cpp)

# Link OpenCV with the library
target_link_libraries(MyLibrary PRIVATE ${OpenCV_LIBS})
target_include_directories(MyLibrary PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Add the executable
add_executable(MyExecutable src/main.cpp)
target_include_directories(MyExecutable PRIVATE ${CMAKE_SOURCE_DIR}/include)


# Link the library and OpenCV with the executable
target_link_libraries(MyExecutable PRIVATE MyLibrary ${OpenCV_LIBS})

# Set the output directories for both the library and the executable
set_target_properties(MyLibrary PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(MyExecutable PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")



# Print status messages
message(STATUS "Using OpenCV version: ${OpenCV_VERSION}")
message(STATUS "Executable and library paths set.")
