# Install script for directory: /home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/AudioDevice.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/AudioStream.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/BoundingBox.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Camera2D.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Camera3D.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Color.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Degree.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Font.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Functions.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Gamepad.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Image.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Material.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Matrix.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Mesh.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Model.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/ModelAnimation.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Mouse.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Music.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Ray.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/RayCollision.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/RaylibException.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/raylib-cpp-utils.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/raylib-cpp.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/raylib.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/raymath.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Rectangle.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/RenderTexture.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Shader.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Sound.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Text.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Texture.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/TextureUnmanaged.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Touch.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Vector2.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Vector3.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Vector4.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/VrStereoConfig.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Wave.hpp"
    "/home/znasif/Assignments/Daniela/381raylib/as1/raylib-cpp/include/Window.hpp"
    )
endif()

