cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

    add_executable(minesweeper main.cpp Class.cpp
            Welcome.h
            Tile.h
            Tile.cpp
            Game.h
    )

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/libraries/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/libraries/SFML/include/SFML)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio)