cmake_minimum_required(VERSION 4.0)
project(Bomberman)
set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    # --- CONFIGURAZIONE PER WINDOWS (MinGW) ---
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libstdc++ -static-libgcc")

    set(CMAKE_PREFIX_PATH "C:/MinGW")
    set(CURSES_LIBRARY "C:/MinGW/lib/libpdcurses.a")
    set(CURSES_INCLUDE_DIR "C:/MinGW/include")

endif()

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIR} )
add_executable( Bomberman
        main.cpp
        Player.cpp
        Player.h
        menu.cpp
        menu.h
        game.cpp
        game.h
        highscore.cpp
        highscore.h
        utility.cpp
        utility.h
        Bomb.cpp
        Bomb.h
)
target_link_libraries( Bomberman ${CURSES_LIBRARIES} )
