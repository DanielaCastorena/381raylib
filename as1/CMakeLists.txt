cmake_minimum_required(VERSION 3.12)
project(as1)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Specify the path to raylib library
set(RAYLIB_DIR "/opt/homebrew/Cellar/raylib/5.0")

# Include the directory containing raylib headers
include_directories(${RAYLIB_DIR}/include)

# Add the path to raylib library
link_directories(${RAYLIB_DIR}/lib)

# Include GLFW
find_package(glfw3 REQUIRED)

# Create executable
add_executable(as1 main.cpp)

# Link raylib and GLFW libraries
target_link_libraries(as0 raylib glfw)

# Define source and destination paths for meshes
set(MESHES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/meshes)
set(MESHES_DEST_DIR ${CMAKE_BINARY_DIR}/meshes)

# Copy meshes to build directory during build
file(COPY ${MESHES_SOURCE_DIR} DESTINATION ${MESHES_DEST_DIR})

# Add custom command to copy individual mesh files
file(GLOB_RECURSE MESH_FILES "${MESHES_SOURCE_DIR}/*.glb")
foreach(MESH_FILE ${MESH_FILES})
    file(COPY ${MESH_FILE} DESTINATION ${MESHES_DEST_DIR})
endforeach()





