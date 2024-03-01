cmake_minimum_required(VERSION 3.12)
project(as3)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")

# Include the directory containing raylib headers
#include_directories(${RAYLIB_DIR}/include)

# Add the path to raylib library
#link_directories(${RAYLIB_DIR}/lib)

# Create executable
add_executable(as3 ${sources})
target_link_libraries(as3 PUBLIC raylib raylib_cpp)
set_property(TARGET as3 PROPERTY CXX_STANDARD 20)
# Link raylib library
#target_link_libraries(as1 raylib)

# Define source and destination paths for meshes
set(MESHES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/meshes)
set(MESHES_DEST_DIR ${CMAKE_BINARY_DIR}/meshes)

# Copy meshes to build directory during build
file(COPY ${MESHES_SOURCE_DIR} DESTINATION ${MESHES_DEST_DIR})

# Define source and destination paths for meshes
set(TEXTURES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/textures)
set(TEXTURES_DEST_DIR ${CMAKE_BINARY_DIR}/textures)

# Copy meshes to build directory during build
file(COPY ${TEXTURES_SOURCE_DIR} DESTINATION ${TEXTURES_DEST_DIR})

# Define source and destination paths for meshes
set(SOUNDS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/sounds)
set(SOUNDS_DEST_DIR ${CMAKE_BINARY_DIR}/sounds)

# Copy meshes to build directory during build
file(COPY ${SOUNDS_SOURCE_DIR} DESTINATION ${SOUNDS_DEST_DIR})