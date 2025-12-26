#include "enemy.h"
#include "Map.h"
#include "Player.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <iostream>
#include <ctime>
#define COLOR_GRAY 8

//superclasse NEMICO
enemy :: enemy(char asp, Map *_mappa) {
    velocita=20000;
    mappa=_mappa;
    do {
        x=rand()%39+1;
        y=rand()%19+1;
    }while (mappa->pos(x,y)!='v');
    tick=0;
    aspetto=asp;
}

int enemy::get_x() {
    return(x);
}

int enemy::get_y() {
    return(y);
}

//stampa nella mappa, utile per stampare quello che passa sopra i muri
void enemy::stamp(WINDOW *win, int start_x, int start_y) {
    start_color();
    init_color(COLOR_GRAY,574,574,574);
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,COLOR_GRAY);
    if (mappa->pos(x,y)=='v') {
        mvwaddch(win,start_y+y,start_x+x,aspetto);
    }
    if (mappa->pos(x,y)=='m') {
        wattron(win,COLOR_PAIR(2));
        mvwaddch(win,start_y+y,start_x+x,aspetto);
        wattroff(win,COLOR_PAIR(2));

    }
    if (mappa->pos(x,y)=='I') {
        wattron(win,COLOR_PAIR(1));
        mvwaddch(win,start_y+y,start_x+x,aspetto);
        wattroff(win,COLOR_PAIR(1));
    }
}

//da fare dopo il wrefresh alla fine del game loop o prima di farlo muovere.
//in modo da cancellare il nemico per poi riaggiornare la stampa (sennò fa una striscia di caratteri)
void enemy::remove_old(WINDOW *win, int start_x, int start_y) {
    start_color();
    init_color(COLOR_GRAY,574,574,574);
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_GRAY,COLOR_GRAY);
    if (mappa->pos(x,y)=='v') {
        mvwaddch(win,start_y+y,start_x+x,' ');
    }
    if (mappa->pos(x,y)=='m') {
        wattron(win,COLOR_PAIR(2));
        mvwaddch(win,start_y+y,start_x+x,'0');
        wattroff(win,COLOR_PAIR(2));

    }
    if (mappa->pos(x,y)=='I') {
        wattron(win,COLOR_PAIR(1));
        mvwaddch(win,start_y+y,start_x+x,'+');
        wattroff(win,COLOR_PAIR(1));
    }
}


//NEMICO BASE (si muove nella stessa direzione finchè non trova un ostacolo)
base_enemy::base_enemy(char asp, Map *_mappa) : enemy (asp,_mappa){
    dir=-1;
}

void base_enemy::move() {
    if (tick>=velocita) {
        while ((dir==0 && (x==1 || mappa->pos(x-1,y)!='v')) || (dir==1 && (y==1 || mappa->pos(x,y-1)!='v')) || (dir==2 && (x==39 || mappa->pos(x+1,y)!='v')) || (dir==3 && (y==19 || mappa->pos(x,y+1)!='v')) || dir==-1) {
            dir=rand()%4;
        }
        if (dir==0) {
            x-=1;
        }
        if (dir==1) {
            y-=1;
        }
        if (dir==2) {
            x+=1;
        }
        if (dir==3) {
            y+=1;
        }
        tick=0;
    }
    else tick++;
}


//NEMICO FORTE (si muove sopra i muri e insegue il player)
advanced_enemy::advanced_enemy(char asp, Map *_mappa) :enemy (asp,_mappa){
}

void advanced_enemy::move(Player pl) {
    if (tick>=velocita) {
        if (pl.get_coordinata_x()==x) {
            if (pl.get_coordinata_y()>y) {
                y+=1;
            }
            else {
                y-=1;
            }
        }
        else if (pl.get_coordinata_y()==y) {
            if (pl.get_coordinata_x()>x) {
                x+=1;
            }
            else {
                x-=1;
            }
        }
        else if (abs(pl.get_coordinata_y()-y)<abs(pl.get_coordinata_x()-x)) {
            if (pl.get_coordinata_y()>y) {
                y+=1;
            }
            else {
                y-=1;
            }
        }
        else if (abs(pl.get_coordinata_x()-x)<abs(pl.get_coordinata_y()-y)) {
            if (pl.get_coordinata_x()>x) {
                x+=1;
            }
            else {
                x-=1;
            }
        }
        tick=0;
    }
    else tick++;
}
