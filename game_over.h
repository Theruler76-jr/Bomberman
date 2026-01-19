#pragma once

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

void game_over_screen(WINDOW *win, int lives, int score, bool times_up);
