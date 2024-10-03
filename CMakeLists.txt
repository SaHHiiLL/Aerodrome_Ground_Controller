cmake_minimum_required(VERSION 3.7)
project(Aerodrome_Ground_Controller C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games


add_subdirectory(libs/raylib)


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
target_link_libraries(${PROJECT_NAME} PRIVATE raylib )
