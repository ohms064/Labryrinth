cmake_minimum_required(VERSION 3.20)

project(Laberinth)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(Laberinth
        src/main.cpp
        src/LabyrinthGrid.h
        src/LabyrinthGrid.cpp
        src/LabyrinthSquare.h
        src/LabyrinthSquare.cpp
)

target_link_libraries(Laberinth PRIVATE raylib)