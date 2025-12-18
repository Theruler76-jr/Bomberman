#include "highscore.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif


char highscore_loop(WINDOW *win) {

    return 'Q';

}