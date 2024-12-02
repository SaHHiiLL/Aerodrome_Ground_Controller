cmake_minimum_required(VERSION 3.7)
project(Aerodrome_Ground_Controller C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# setting raylib path
set(RAYLIB_DIR "./libs/raylib-5.0/")

find_library(RAYLIB_LIBRARY NAMES raylib HINTS ${RAYLIB_DIR}/lib)
include_directories(${RAYLIB_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Runway.cpp
        src/Runway.h
        src/Coordinates.cpp
        src/Coordinates.h
        src/Utils.cpp
        src/RunwayCenterline.h
        src/RunwayCenterline.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY})
