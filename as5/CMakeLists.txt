cmake_minimum_required(VERSION 3.12)
project(as5)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")

# Include the directory containing raylib headers
#include_directories(${RAYLIB_DIR}/include)

# Add the path to raylib library
#link_directories(${RAYLIB_DIR}/lib)

# Create executable
add_executable(as5 ${sources})
target_link_libraries(as5 PUBLIC raylib raylib_cpp)
set_property(TARGET as5 PROPERTY CXX_STANDARD 20)
# Link raylib library
#target_link_libraries(as5 raylib)