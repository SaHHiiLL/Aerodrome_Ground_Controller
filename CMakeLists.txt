cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 23)
project(Aerodrome_Ground_Controller)

# setting raylib path
set(RAYLIB_DIR libs/raylib/)
set(DELAUNATOR libs/delaunator/)
set(IMGUI_DIR libs/imgui/)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wextra")

find_library(
  RAYLIB_LIBRARY
  NAMES raylib
  PATHS ${RAYLIB_DIR}/lib REQUIRED)

find_library(
  IMGUI_LIBRARY
  NAMES imgui
  PATHS ${IMGUI_DIR}/build/lib)

message(STATUS "Found library: ${IMGUI_LIBRARY}")

# Include directories
include_directories(libs/raylib/include)
include_directories(libs/triangulation)
include_directories(libs/lexer)
include_directories(libs/imgui/include)

file(GLOB TRI_CXX_SRC "${PROJECT_SOURCE_DIR}/libs/triangulation/*.cpp")

# Add the executable
add_executable(
  Aerodrome_Ground_Controller
  # external Libs #
  ${TRI_CXX_SRC}
  src/colours/ColourParser.cpp
  src/colours/ColourParser.hpp
  src/colours/Colours.cpp
  src/colours/Colours.hpp
  src/polygon/Polygon.cpp
  src/polygon/Polygon.hpp
  src/polygon/PolygonParser.cpp
  src/polygon/PolygonParser.hpp
  src/AGCException.hpp
  src/Coordinate.cpp
  src/Coordinate.hpp
  src/earcutter.cpp
  src/earcutter.hpp
  src/Game.cpp
  src/Game.hpp
  src/main.cpp
  src/ResourceManager.cpp
  src/ResourceManager.hpp
  src/Quadrilateral.cpp
  src/Quadrilateral.hpp
  src/Utils.cpp
  src/Utils.hpp
  src/labels/LabelParser.hpp
  src/labels/LabelParser.cpp)

target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARY} ${IMGUI_LIBRARY})
