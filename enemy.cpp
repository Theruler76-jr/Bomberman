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
#define tempo_danno 15

//superclasse NEMICO
enemy :: enemy(Map *_mappa) {
    velocita=10;
    mappa=_mappa;
    do {
        x=rand()%39+1;
        y=rand()%19+1;
    }while (mappa->pos(x,y)!='v');
    tick=0;
    count_down_danno=0;
}

int enemy::get_x() {
    return(x);
}

int enemy::get_y() {
    return(y);
}

//NEMICO BASE (si muove nella stessa direzione finchè non trova un ostacolo)
base_enemy::base_enemy(Map *_mappa) : enemy (_mappa){
    aspetto='#';
    dir=-1;
    mappa->cambia(x,y,'#');
}

void base_enemy::move(Player *pl) {
    if (tick>=velocita) {
        if (mappa->pos(x-1,y)=='v' || mappa->pos(x,y-1)=='v' || mappa->pos(x+1,y)=='v' || mappa->pos(x,y+1)=='v' || mappa->pos(x-1,y)=='@' || mappa->pos(x,y-1)=='@' || mappa->pos(x+1,y)=='@' || mappa->pos(x,y+1)=='@') {
            //rimetto il vuoto sotto
            mappa->cambia(x,y,'v');
            while ((dir==0 && (x==1 || (mappa->pos(x-1,y)!='v' && mappa->pos(x-1,y)!='@') )) || (dir==1 && (y==1 || (mappa->pos(x,y-1)!='v' && mappa->pos(x,y-1)!='@'))) || (dir==2 && (x==39 || (mappa->pos(x+1,y)!='v' && mappa->pos(x+1,y)!='@') )) || (dir==3 && (y==19 || (mappa->pos(x,y+1)!='v' && mappa->pos(x,y+1)!='@') )) || dir==-1) {
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

            //nuova posizione del nemico
            mappa->cambia(x,y,'#');
        }
    }
    else tick++;

    //danno al player
    if (pl->get_coordinata_x()==x && pl->get_coordinata_y()==y && count_down_danno<=0) {
        pl->cambia_numero_vite(-1);
        count_down_danno=tempo_danno;
    }

    if (count_down_danno>0) {
        count_down_danno--;
    }
}


//NEMICO FORTE (si muove sopra i muri e insegue il player)
advanced_enemy::advanced_enemy(Map *_mappa) :enemy (_mappa){
    aspetto='%';
    mappa->cambia(x,y,'%');
    velocita=20;
}

void advanced_enemy::move(Player *pl) {
    if (tick>=velocita) {
        if (pl->get_coordinata_x()!=x || pl->get_coordinata_y()!=y) {
            //se è sul vuoto
            if (mappa->pos(x,y)=='%') {
                mappa->cambia(x,y,'v');
            }

            //se è su un muro distruttibile
            if (mappa->pos(x,y)=='x') {
                mappa->cambia(x,y,'m');
            }

            //se è su un muro indistruttibile
            if (mappa->pos(x,y)=='z') {
                mappa->cambia(x,y,'I');
            }


            if (pl->get_coordinata_x()==x) {
                if (pl->get_coordinata_y()>y) {
                    y+=1;
                }
                else {
                    y-=1;
                }
            }
            else if (pl->get_coordinata_y()==y) {
                if (pl->get_coordinata_x()>x) {
                    x+=1;
                }
                else {
                    x-=1;
                }
            }
            else if (abs(pl->get_coordinata_y()-y)<abs(pl->get_coordinata_x()-x)) {
                if (pl->get_coordinata_y()>y) {
                    y+=1;
                }
                else {
                    y-=1;
                }
            }
            else if (abs(pl->get_coordinata_x()-x)<abs(pl->get_coordinata_y()-y)) {
                if (pl->get_coordinata_x()>x) {
                    x+=1;
                }
                else {
                    x-=1;
                }
            }
            tick=0;

            //se è sul vuoto
            if (mappa->pos(x,y)=='v') {
                mappa->cambia(x,y,'%');
            }

            //se è su un muro distruttibile
            if (mappa->pos(x,y)=='m') {
                mappa->cambia(x,y,'x');
            }

            //se è su un muro indistruttibile
            if (mappa->pos(x,y)=='I') {
                mappa->cambia(x,y,'z');
            }
        }
    }
    else tick++;

    //danno al player
    if (pl->get_coordinata_x()==x && pl->get_coordinata_y()==y && count_down_danno<=0) {
        pl->cambia_numero_vite(-1);
        count_down_danno=tempo_danno;
    }

    if (count_down_danno>0) {
        count_down_danno--;
    }
}