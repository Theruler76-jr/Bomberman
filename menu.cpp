#include "menu.h"

#include <ncurses/ncurses.h>
#include <stdlib.h>


char menu_loop(WINDOW *win) {


    char input;

    while (true) {

        input = getch();

        switch (input) {
            case 'q':
            return 'Q';
        }

        // Logica





        // disegno

        box(win, 0, 0);



        wrefresh(win);
        refresh();
        _sleep(100);

    }

}