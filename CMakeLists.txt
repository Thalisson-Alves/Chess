cmake_minimum_required(VERSION 3.20)
project(Chess)

set(CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")

add_executable(Chess main.cpp Game.cpp Game.h
        src/Board.cpp
        src/Piece.cpp
        src/Bishop.cpp src/Bishop.h src/King.cpp src/King.h src/Pawn.cpp src/Pawn.h src/Queen.cpp src/Queen.h src/Rook.cpp src/Rook.h src/Knight.cpp src/Knight.h src/NullPiece.cpp src/NullPiece.h src/Application.h src/Globals.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)

target_link_libraries(Chess sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
