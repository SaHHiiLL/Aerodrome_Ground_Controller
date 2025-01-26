cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 23)
project(Aerodrome_Ground_Controller)

# setting raylib path
set(RAYLIB_DIR libs/raylib/)
set(DELAUNATOR libs/delaunator/)
set(IMGUI_DIR libs/imgui/)
set(SPDLOG_DIR libs/spdlog/)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wextra")

find_package(spdlog NAMES spdlog HINTS ${SPDLOG_DIR}/ REQUIRED)

find_library(
  RAYLIB_LIBRARY
  NAMES raylib
  PATHS ${RAYLIB_DIR}/lib REQUIRED)

find_library(
  IMGUI_LIBRARY
  NAMES imgui
  PATHS ${IMGUI_DIR}/build/lib)

# Include directories
include_directories(libs/raylib/include)
include_directories(libs/triangulation)
include_directories(libs/lexer)
include_directories(libs/imgui/include)
include_directories(${SPDLOG_DIR}/include)

file(GLOB TRI_CXX_SRC "${PROJECT_SOURCE_DIR}/libs/triangulation/*.cpp")
file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Add the executable
add_executable(
  Aerodrome_Ground_Controller
  # external Libs #
  ${TRI_CXX_SRC} ${SRC})

target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARY} ${IMGUI_LIBRARY}
                      spdlog::spdlog_header_only)
