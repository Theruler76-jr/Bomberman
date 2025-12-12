#include "game.h"

#include <ncurses/ncurses.h>


struct Level {
    Map map();

    int time = 60 * 5;

    Level *previous = nullptr;
    Level *next = nullptr;
};


char game_loop(WINDOW *win) {

    char input;

    Level *current_level;

    int score = 0;

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


