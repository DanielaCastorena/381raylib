# CMakeLists.txt in the as0 folder

cmake_minimum_required(VERSION 3.12)
project(as0)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Specify the path to Raylib library
set(RAYLIB_DIR "/opt/homebrew/Cellar/raylib/5.0")

# Include the directory containing Raylib headers
include_directories(${RAYLIB_DIR}/include)

# Add the path to Raylib library
link_directories(${RAYLIB_DIR}/lib)

# Include GLFW
find_package(glfw3 REQUIRED)

# Create executable
add_executable(as0 main.cpp)

# Link Raylib and GLFW libraries
target_link_libraries(as0 raylib glfw)


