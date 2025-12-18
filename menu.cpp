#include "menu.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif
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