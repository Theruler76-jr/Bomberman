#include "menu.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif
#include <stdlib.h>


char menu_loop(WINDOW *win) {

    keypad(win, TRUE);

    int input;
    const char *menu[3] {"New Game", "Leaderboard", "Quit"};
    int selection = 0;

    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);

    while (true) {

        input = wgetch(win);


        switch (input) {
            case 'q':
                return 'Q';

            case KEY_UP:
                if (selection > 0) selection--;
                break;

            case KEY_DOWN:
                if (selection < 2) selection++;
                break;

            case 10:

                switch (selection) {
                    case 0:
                        return 'G';
                    case 1:
                        return 'H';
                    case 2:
                        return 'Q';
                    default:
                        return 'E';
                }

            default:
                break;
        }

        // Logica





        // disegno

        box(win, 0, 0);

        mvwprintw(win, LINES - 1, 0, "MENU");

        for (int i = 0; i < 3; i++) {

            if (selection == i) {
                wattron(win, COLOR_PAIR(1));
                wattron(win, A_BLINK);
            }

            mvwprintw(win, 10 + i, 5, "%s", menu[i]);

            wattroff(win, COLOR_PAIR(1));
            wattroff(win, A_BLINK);

        }

        wprintw(win, "%d", selection);


        wrefresh(win);
        //refresh();
    }

}