cmake_minimum_required(VERSION 3.12)
project(as0)

#set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

#specify the path to raylib library
set(RAYLIB_DIR "/opt/homebrew/Cellar/raylib/5.0")

#include the directory containing raylib headers
include_directories(${RAYLIB_DIR}/include)

#add the path to raylib library
link_directories(${RAYLIB_DIR}/lib)

#include GLFW
find_package(glfw3 REQUIRED)

#create executable
add_executable(as0 main.cpp)

#link raylib and GLFW libraries
target_link_libraries(as0 raylib glfw)

# Define source and destination paths for textures
set(TEXTURES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/textures)
set(TEXTURES_DEST_DIR ${CMAKE_BINARY_DIR}/textures)

# Copy textures to build directory during build
file(COPY ${TEXTURES_SOURCE_DIR} DESTINATION ${TEXTURES_DEST_DIR})

# Define source and destination paths for meshes
set(MESHES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/meshes)
set(MESHES_DEST_DIR ${CMAKE_BINARY_DIR}/meshes)

# Copy meshes to build directory during build
file(COPY ${MESHES_SOURCE_DIR} DESTINATION ${MESHES_DEST_DIR})




