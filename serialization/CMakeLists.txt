cmake_minimum_required(VERSION 3.1)

# Set project name and C++ standard
project(MyProject)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV (version 4 or later) and include necessary components
find_package(OpenCV 4 REQUIRED COMPONENTS xfeatures2d imgcodecs)

# Define the `mat_serialization` library
add_library(mat_serialization src/serialize.cpp)
target_include_directories(mat_serialization PUBLIC include)
target_link_libraries(mat_serialization PUBLIC ${OpenCV_LIBS}) # Use PUBLIC for propagating OpenCV

# Define the `convert_dataset` library
add_library(convert_dataset src/convert_dataset.cpp)
target_include_directories(convert_dataset PUBLIC include)
target_link_libraries(convert_dataset PUBLIC ${OpenCV_LIBS} mat_serialization)

# Add the tests subdirectory
add_executable(main main.cpp)
target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(main PUBLIC include)
target_link_libraries(main ${CMAKE_BINARY_DIR}/libmat_serialization.a ${OpenCV_LIBS})
