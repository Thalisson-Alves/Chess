cmake_minimum_required(VERSION 3.20)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess main.cpp Game.cpp
        src/Board.cpp
        src/Piece.cpp
        src/Bishop.cpp
        src/King.cpp
        src/Pawn.cpp
        src/Queen.cpp
        src/Rook.cpp
        src/Knight.cpp
        src/NullPiece.cpp
        src/Globals.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)

target_link_libraries(Chess sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
