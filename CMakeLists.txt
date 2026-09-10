cmake_minimum_required(VERSION 3.16)

project(chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(chess
    src/main.cpp
    src/Game.cpp
    src/Input.cpp
    src/Piece.cpp
    src/Rook.cpp
    src/Knight.cpp
    src/Bishop.cpp
    src/Queen.cpp
    src/King.cpp
    src/Pawn.cpp
    src/Square.cpp
    src/Board.cpp
    src/Position.cpp
    src/Graphics.cpp
)

target_include_directories(chess
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
