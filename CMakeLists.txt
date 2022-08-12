cmake_minimum_required(VERSION 3.20)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS window graphics audio REQUIRED)

add_executable(minesweeper minesweeper.cpp Toolbox.h Toolbox.cpp GameState.h GameState.cpp Button.h Tile.h Tile.cpp minesweeper.h)
target_link_libraries(minesweeper sfml-graphics sfml-audio)