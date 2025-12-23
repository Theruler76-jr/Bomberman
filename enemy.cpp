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

//superclasse NEMICO
enemy :: enemy(int vel, char asp, Map *_mappa) {
    velocità=vel;
    mappa=_mappa;
    do {
        x=rand()%39+1;
        y=rand()%19+1;
    }while (mappa->pos(x,y)=='v');
    tick=0;
    aspetto=asp;
}

int enemy::get_x() {
    return(x);
}

int enemy::get_y() {
    return(y);
}

void enemy::stamp(WINDOW *win) {
    mvwaddch(win,x,y,aspetto);
}


//NEMICO BASE (si muove nella stessa direzione finchè non trova un ostacolo)
base_enemy::base_enemy(int vel, char asp, Map *_mappa) : enemy (vel,asp,_mappa){
    dir=-1;
}

void base_enemy::move() {
    if (tick>=velocità) {
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
void advanced_enemy::move(Player pl) {
    if (tick>=velocità) {
        if (pl.get_coordinata_x()==x || abs(pl.get_coordinata_y()-y)<abs(pl.get_coordinata_x()-x)) {
            if (pl.get_coordinata_y()>y) {
                y+=1;
            }
            else {
                y-=1;
            }
        }
        else if (pl.get_coordinata_y()==y || abs(pl.get_coordinata_x()-x)<abs(pl.get_coordinata_y()-y)) {
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
