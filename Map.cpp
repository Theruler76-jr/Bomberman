#include "Map.h"
#include <iostream>
#include <cmath>
#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif
#define COLOR_GRAY 8

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
                map[i][j]='v';
            }
            else {
                map[i][j]='v';
            }
            map[10][0]='v';
            map[10][40]='v';
        }
    }
}

void Map::livello(int lv) {
    int n_muri=120*(int)sqrt(lv);
    srand(time(0));
    while (n_muri>0){
        int x=rand()%39+1;
        int y=rand()%19+1;
        if ((x!=1 || y!=1) && (x!=2 || y!=1) && (x!=3 || y!=1) && (x!=1 || y!=2) && map[y][x]=='v') {
            map[y][x]='m';
            n_muri--;
        }
    }
}

void Map::stamp(WINDOW *win) {
    start_color();
    init_color(COLOR_GRAY,574,574,574);
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_GRAY,COLOR_GRAY);
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


//test per stampare i livelli
/*
int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    Map x;
    x.livello(1);
    WINDOW *win=newwin(21,41,0,0);
    x.stamp(win);

    getch();
    endwin();
}
*/