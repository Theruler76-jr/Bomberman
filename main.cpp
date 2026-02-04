#include "menu.h"
#include "game.h"
#include "highscore.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <iostream>


int main() {

    initscr();
#ifdef _WIN32
    resize_term(0, 0);
#endif

    refresh();

    curs_set(0); // nasconde il cursore di desttesto
    noecho(); // non fa stampare alla console i tasti che preme l'utente
    nodelay(stdscr, TRUE);
    cbreak(); // permette l'uso di Ctrl + C per interrompere il programma
    keypad(stdscr, TRUE); // permette l'uso del keypad

    //controllo terminale troppo piccolo
    int height=LINES, width=COLS;

    while(height<31 || width<121){
        int ch = getch();
        int y=height/2;
        int x=width/2-12;
        if (x<0) x=0;
        clear();
        mvprintw(y,x,"TERMINALE TROPPO PICCOLO!");
        refresh();

        height=LINES;
        width=COLS;
    }

    WINDOW *win = newwin(height, width, 0, 0);

    refresh();

    char state = 'M';
    bool quit = false;

    while (!quit) {

        switch (state) {

            case 'M':
                state = menu_loop(win);
                break;

            case 'G':
                state = game_loop(win, width, height);
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
