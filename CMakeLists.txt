cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 23)
project(Aerodrome_Ground_Controller)

# setting raylib path
set(RAYLIB_DIR "${PROJECT_SOURCE_DIR}/libs/raylib/")
set(DELAUNATOR "${PROJECT_SOURCE_DIR}/libs/delaunator/")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

find_library(
  RAYLIB_LIBRARY
  NAMES raylib
  HINTS ${RAYLIB_DIR}/lib)

# Include directories
include_directories(${RAYLIB_DIR}/include)
include_directories(${DELAUNATOR})
include_directories(libs/raylib/include)
include_directories(libs/triangulation)

# Add the executable
add_executable(
  Aerodrome_Ground_Controller
  libs/triangulation/delaunator.cpp
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
  src/Utils.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY})
