cmake_minimum_required(VERSION 4.0)
project(Bomberman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --static -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/MinGW")
set(CURSES_INCLUDE_PATH "C:/MinGW/include")
set(CURSES_LIBRARY "C:/MinGW/lib/libpdcurses.a")

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIR} )
add_executable( Bomberman main.cpp
        Player.cpp
        Player.h
        menu.cpp)
target_link_libraries( Bomberman ${CURSES_LIBRARIES} )
