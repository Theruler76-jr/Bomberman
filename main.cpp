#include <iostream>
#include <ncurses/ncurses.h>

#include "menu.h"
#include "game.h"
#include "highscore.h"

int main() {

    initscr();

    WINDOW *win = newwin(10, 10, 0, 0);

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
                exit(-1);

        }

    }

    endwin();

    return 0;

}
