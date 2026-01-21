#include "enemy.h"

#include "Bomb.h"
#include "game.h"
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
        x=rand()%35+5;
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

enemy::~enemy() {

}

//NEMICO BASE (si muove nella stessa direzione finchè non trova un ostacolo)
base_enemy::base_enemy(Map *_mappa) : enemy (_mappa){
    aspetto='#';
    dir=-1;
    mappa->cambia(x,y,'#');
}

void base_enemy::move(Player *pl) {
    if (tick>=velocita) {
        if (mappa->pos(x-1,y)=='v' || mappa->pos(x,y-1)=='v' || mappa->pos(x+1,y)=='v' || mappa->pos(x,y+1)=='v' || mappa->pos(x-1,y)=='@' || mappa->pos(x,y-1)=='@' || mappa->pos(x+1,y)=='@' || mappa->pos(x,y+1)=='@' || mappa->pos(x-1,y)==bomb_exp || mappa->pos(x,y-1)==bomb_exp|| mappa->pos(x+1,y)==bomb_exp || mappa->pos(x,y+1)==bomb_exp) {

            //caso bomba
            if (mappa->pos(x,y)==bomb_exp) {
                mappa->cambia(x,y,bomb_exp);
            }
            //rimetto il player sotto
            else if (pl->get_coordinata_x()==x && pl->get_coordinata_y()==y) {
                mappa->cambia(x,y,'@');
            }
            //caso bomba
            else if (mappa->pos(x,y)==bomb_exp) {
                mappa->cambia(x,y,bomb_exp);
            }
            //caso vuoto
            else{
                mappa->cambia(x,y,'v');
            }

            while ((dir==0 && (x==1 || (mappa->pos(x-1,y)!='v' && mappa->pos(x-1,y)!='@' && mappa->pos(x-1,y)!=bomb_exp) )) || (dir==1 && (y==1 || (mappa->pos(x,y-1)!='v' && mappa->pos(x,y-1)!='@' && mappa->pos(x,y-1)!=bomb_exp))) || (dir==2 && (x==39 || (mappa->pos(x+1,y)!='v' && mappa->pos(x+1,y)!='@' && mappa->pos(x+1,y)!=bomb_exp) )) || (dir==3 && (y==19 || (mappa->pos(x,y+1)!='v' && mappa->pos(x,y+1)!='@' && mappa->pos(x,y+1)!=bomb_exp) )) || dir==-1) {
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
            if (mappa->pos(x,y)==bomb_exp) {
                mappa->cambia(x,y,bomb_exp);
            }
            else {
                mappa->cambia(x,y,'#');
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

void base_enemy::punteggio(int &score) {
    score+=score_per_enemy;
}

//NEMICO FORTE (si muove sopra i muri e insegue il player)
advanced_enemy::advanced_enemy(Map *_mappa) :enemy (_mappa){
    do {
        x=rand()%20+20;
        y=rand()%19+1;
    }while (mappa->pos(x,y)!='v');
    aspetto='%';
    mappa->cambia(x,y,'%');
    velocita=20;
}

void advanced_enemy::move(Player *pl) {
    if (tick>=velocita) {
        if (pl->get_coordinata_x()!=x || pl->get_coordinata_y()!=y) {
            //se era su una bomba esplosa
            if (mappa->pos(x,y)==bomb_exp) {
                mappa->cambia(x,y,bomb_exp);
            }
            //se è sul vuoto
            else if (mappa->pos(x,y)=='%') {
                mappa->cambia(x,y,'v');
            }

            //se è su un muro distruttibile
            else if (mappa->pos(x,y)=='x') {
                mappa->cambia(x,y,'m');
            }

            //se è su un muro indistruttibile
            else if (mappa->pos(x,y)=='z') {
                mappa->cambia(x,y,'I');
            }
            //se era sul player
            else if (pl->get_coordinata_x()==x && pl->get_coordinata_y()==y) {
                mappa->cambia(x,y,'@');
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

            //se è su una bomba
            if (mappa->pos(x,y)==bomb_exp) {
                mappa->cambia(x,y,bomb_exp);
            }

            //se è sul vuoto
            else if (mappa->pos(x,y)=='v') {
                mappa->cambia(x,y,'%');
            }

            //se è su un muro distruttibile
            else if (mappa->pos(x,y)=='m') {
                mappa->cambia(x,y,'x');
            }

            //se è su un muro indistruttibile
            else if (mappa->pos(x,y)=='I') {
                mappa->cambia(x,y,'z');
            }

            //se è sul player
            else if (mappa->pos(x,y)==player_skin) {
                mappa->cambia(x,y,'%');
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

void advanced_enemy::punteggio(int &score) {
    score+=score_per_enemy+5;
}
