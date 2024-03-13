cmake_minimum_required(VERSION 3.12)
project(as5)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(raylib-cpp)

# Glob source files
file(GLOB_RECURSE sources "src/*.cpp" "src/*.c")

# Add the directory containing raylib headers
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/raylib-cpp/raylib/src
    ${CMAKE_CURRENT_SOURCE_DIR}/raylib-cpp/raygui/src
)

# Create executable
add_executable(as5 ${sources} src/VolumeControl.cpp)

# Link against raylib library (provided by raylib-cpp)
target_link_libraries(as5 PRIVATE raylib)

# Define source and destination paths for meshes
set(AUDIO_SOURCE_DIR ${CMAKE_SOURCE_DIR}/audio)
set(AUDIO_DEST_DIR ${CMAKE_BINARY_DIR}/audio)

# Copy meshes to build directory during build
file(COPY ${AUDIO_SOURCE_DIR} DESTINATION ${AUDIO_DEST_DIR})





