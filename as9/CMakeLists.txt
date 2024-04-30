cmake_minimum_required(VERSION 3.20)
project(DuckLib LANGUAGES CXX)

include(includeable.cmake)
add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")
add_executable(as9 ${sources})
target_link_libraries(as9 PUBLIC raylib raylib_cpp)
set_property(TARGET as9 PROPERTY CXX_STANDARD 20)

configure_file(textures/ball.jpeg textures/ball.jpeg COPYONLY)
configure_file(textures/paddle.png textures/paddle.png COPYONLY)
configure_file(textures/block.png textures/block.png COPYONLY)
configure_file(sounds/background.mp3 sounds/background.mp3 COPYONLY)