#include <iostream>
#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include "menu.h"
#include "game.h"
#include "highscore.h"


int main() {

    initscr();

    noecho(); // non fa stampare alla console i tasti che preme l'utente
    nodelay(stdscr, TRUE);
    cbreak();
    keypad(stdscr, TRUE);

    int width, height;
    getmaxyx(stdscr, height, width);

    width = 40;
    height = 20;

    WINDOW *win = newwin(height, width, 0, 0);

    refresh();

    //std::cout << "size: " << width << ", " << height << std::endl;

    char state = 'M';
    bool quit = false;

    while (!quit) {

        switch (state) {

            case 'M':
                state = menu_loop(win);
                break;

            case 'G':
                state = game_loop(win);
                break;

            case 'H':
                state = highscore_loop(win);
                break;

            case 'Q':
                quit = true;
                break;

            default:
                std::cout << "Invalid state " <<  state << std::endl;
                exit(-1);

        }

    }

    endwin();
    return 0;

}
