#pragma once
#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

class Map {
protected:
    int row=20, col=40;
    char map[20][40];
public:
    Map();

    void livello (int lv);

    void stamp (WINDOW *win);
};