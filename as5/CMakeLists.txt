cmake_minimum_required(VERSION 3.12)
project(as5)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Include raylib-cpp submodule
add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")

# Create executable
add_executable(as5 ${sources})

# Include directories for raylib-cpp and raylib
target_include_directories(as5 PRIVATE raylib-cpp/include)
target_include_directories(as5 PRIVATE raylib-cpp/src)

# Link against raylib-cpp
target_link_libraries(as5 PRIVATE raylib-cpp)

# Define source and destination paths for meshes
set(AUDIO_SOURCE_DIR ${CMAKE_SOURCE_DIR}/audio)
set(AUDIO_DEST_DIR ${CMAKE_BINARY_DIR}/audio)

# Copy meshes to build directory during build
file(COPY ${AUDIO_SOURCE_DIR} DESTINATION ${AUDIO_DEST_DIR})






