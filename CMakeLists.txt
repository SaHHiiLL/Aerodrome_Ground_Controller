cmake_minimum_required(VERSION 3.29)
project(Aerodrome_Ground_Controller)

set(CMAKE_CXX_STANDARD 23)

# Include directories
include_directories(libs/raylib-5.0_linux_amd64/include)
include_directories(libs/triangulation)
include_directories(src)
include_directories(src/colours)
include_directories(src/polygon)

# setting raylib path
set(RAYLIB_DIR "./libs/raylib-5.0/")

find_library(RAYLIB_LIBRARY NAMES raylib HINTS ${RAYLIB_DIR}/lib)
include_directories(${RAYLIB_DIR}/include)

# Add the executable
add_executable(Aerodrome_Ground_Controller
        libs/triangulation/delaunator.cpp
        libs/triangulation/delaunator.hpp
        src/colours/ColourParser.cpp
        src/colours/ColourParser.hpp
        src/colours/Colours.cpp
        src/colours/Colours.hpp
        src/polygon/Polygon.cpp
        src/polygon/Polygon.hpp
        src/polygon/PolygonParser.cpp
        src/polygon/PolygonParser.hpp
        src/AGCException.hpp
        src/Coordinates.cpp
        src/Coordinates.hpp
        src/earcutter.cpp
        src/earcutter.hpp
        src/Game.cpp
        src/Game.hpp
        src/main.cpp
        src/ResourceManager.cpp
        src/ResourceManager.hpp
        src/Runway.cpp
        src/Runway.hpp
        src/Utils.cpp
        src/Utils.hpp)


target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY})
