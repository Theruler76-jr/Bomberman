#include <iostream>
#include <ncurses/ncurses.h>

#include "menu.h"

int main() {

    initscr();

    WINDOW *win = newwin(10, 10, 0, 0);

    char state = 'M';

    while (true) {

        switch (state) {

            case 'M':
                state = menu_loop(win);
                break;

            // case 'G':
            //     state = game_loop(win);
            //     break;
            //
            // case 'H':
            //     state = highscore_loop(win);
            //     break;

            case 'Q':
                endwin();
                return 0;

            default:
                endwin();
                exit(1);

        }

    }

}
