#include "Map.h"
#include <iostream>
#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

Map :: Map () {
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            if (i==0 || j==0 || i==(row-1) || j==col-1) {
                map[i][j]='I';
            }
            else if ((i+j)%2==0 && i%2==0) {
                map[i][j]='I';
            }
            else if (i==1 || j==1 || i==(row-2) || j==(col-2)) {
                map[i][j]='c';
            }

            else {
                map[i][j]='c';
            }
        }
    }
}

void Map::stamp(WINDOW *win) {
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,8);
    box(win,0,0);
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            if (map[i][j]=='I') {
                wattron(win,COLOR_PAIR(1));
                mvwaddch(win,i,j,' ');
                wattroff(win,COLOR_PAIR(1));
            }
            if (map[i][j]=='m') {
                wattron(win,COLOR_PAIR(2));
                mvwaddch(win,i,j,' ');
                wattroff(win,COLOR_PAIR(2));
            }
        }
    }
    refresh();
    wrefresh(win);
}

void Map::livello(int lv) {
    int n_muri=65*lv;
    srand(time(0));
    while (n_muri>0){
        int x=rand()%38+1;
        int y=rand()%18+1;
        if ((x!=1 || y!=1) && (x!=2 || y!=1) && (x!=3 || y!=1) && (x!=1 || y!=2) && map[y][x]=='c') {
            map[y][x]='m';
            n_muri--;
        }
    }
}


int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    Map x;
    x.livello(5);
    WINDOW *win=newwin(20,40,0,0);
    x.stamp(win);

    getch();
    endwin();
}