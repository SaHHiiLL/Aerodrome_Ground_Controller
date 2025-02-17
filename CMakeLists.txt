cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 23)
project(Aerodrome_Ground_Controller)

option(ENABLE_DEBUG "Enable debug mode" OFF)

# setting raylib path
set(RAYLIB_DIR libs/raylib)
set(DELAUNATOR libs/delaunator)
set(IMGUI_DIR libs/imgui)
set(SPDLOG_DIR libs/spdlog)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wextra")

find_library(
  RAYLIB_LIBRARY
  NAMES raylib
  PATHS ${RAYLIB_DIR}/lib REQUIRED)

get_filename_component(RL_BRIDGE_RAYLIB_LIBRARY_DIR
                       "${CMAKE_CURRENT_SOURCE_DIR}/${RAYLIB_DIR}" ABSOLUTE)
add_subdirectory(${IMGUI_DIR})
add_subdirectory(${SPDLOG_DIR})

# Include directories
include_directories(libs/raylib/include)
include_directories(libs/triangulation)
include_directories(libs/lexer)
include_directories(libs/imgui/include)

file(GLOB TRI_CXX_SRC "${PROJECT_SOURCE_DIR}/libs/triangulation/*.cpp")
file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Add the executable
add_executable(Aerodrome_Ground_Controller ${TRI_CXX_SRC} ${SRC})

if(ENABLE_DEBUG)
  target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARY} imgui spdlog)
