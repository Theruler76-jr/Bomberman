#include "menu.h"

#include <stdlib.h>
#include <ncurses/ncurses.h>


char menu_loop(WINDOW *win) {


    char input;

    while (true) {

        input = getch();

        switch (input) {
            case 'q':
            return 'Q';
        }



        box(win, 0, 0);



        wrefresh(win);
        refresh();
        _sleep(100);
    }

    return 'Q';

}