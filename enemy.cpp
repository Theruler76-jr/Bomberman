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
    }while (mappa->pos(x,y)!=vuoto);
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
    aspetto=base_en;
    dir=-1;
    mappa->cambia(x,y,base_en);
}

void base_enemy::move(Player *pl) {
    if (tick>=velocita) {
        if (mappa->pos(x-1,y)==vuoto || mappa->pos(x,y-1)==vuoto || mappa->pos(x+1,y)==vuoto || mappa->pos(x,y+1)==vuoto
            || mappa->pos(x-1,y)==player_skin || mappa->pos(x,y-1)==player_skin || mappa->pos(x+1,y)==player_skin || mappa->pos(x,y+1)==player_skin
            || mappa->pos(x-1,y)==bomb_exp || mappa->pos(x,y-1)==bomb_exp|| mappa->pos(x+1,y)==bomb_exp || mappa->pos(x,y+1)==bomb_exp
            || mappa->pos(x-1,y)==item_l || mappa->pos(x,y-1)==item_l|| mappa->pos(x+1,y)==item_l || mappa->pos(x,y+1)==item_l
            || mappa->pos(x-1,y)==item_r || mappa->pos(x,y-1)==item_r|| mappa->pos(x+1,y)==item_r || mappa->pos(x,y+1)==item_r
            || mappa->pos(x-1,y)==item_n || mappa->pos(x,y-1)==item_n|| mappa->pos(x+1,y)==item_n || mappa->pos(x,y+1)==item_n
            || mappa->pos(x-1,y)==item_t || mappa->pos(x,y-1)==item_t|| mappa->pos(x+1,y)==item_t || mappa->pos(x,y+1)==item_t
            || mappa->pos(x-1,y)==item_p || mappa->pos(x,y-1)==item_p|| mappa->pos(x+1,y)==item_p || mappa->pos(x,y+1)==item_p) {

            //caso bomba/item
            if (mappa->pos(x,y)==bomb_exp
                || mappa->pos(x,y)==item_l
                || mappa->pos(x,y)==item_r
                || mappa->pos(x,y)==item_n
                || mappa->pos(x,y)==item_t
                || mappa->pos(x,y)==item_p) {
            }
            //rimetto il player sotto
            else if (pl->get_coordinata_x()==x && pl->get_coordinata_y()==y) {
                mappa->cambia(x,y,player_skin);
            }
            //caso vuoto
            else{
                mappa->cambia(x,y,vuoto);
            }

            while ((dir==0 && (x==1 || (mappa->pos(x-1,y)!=vuoto && mappa->pos(x-1,y)!=player_skin && mappa->pos(x-1,y)!=bomb_exp && mappa->pos(x-1,y)!=item_l && mappa->pos(x-1,y)!=item_r && mappa->pos(x-1,y)!=item_n && mappa->pos(x-1,y)!=item_t && mappa->pos(x-1,y)!=item_p) ))
                || (dir==1 && (y==1 || (mappa->pos(x,y-1)!=vuoto && mappa->pos(x,y-1)!=player_skin && mappa->pos(x,y-1)!=bomb_exp && mappa->pos(x,y-1)!=item_l && mappa->pos(x,y-1)!=item_r && mappa->pos(x,y-1)!=item_n && mappa->pos(x,y-1)!=item_t && mappa->pos(x,y-1)!=item_p)))
                || (dir==2 && (x==39 || (mappa->pos(x+1,y)!=vuoto && mappa->pos(x+1,y)!=player_skin && mappa->pos(x+1,y)!=bomb_exp && mappa->pos(x+1,y)!=item_l && mappa->pos(x+1,y)!=item_r && mappa->pos(x+1,y)!=item_n && mappa->pos(x+1,y)!=item_t && mappa->pos(x+1,y)!=item_p) ))
                || (dir==3 && (y==19 || (mappa->pos(x,y+1)!=vuoto && mappa->pos(x,y+1)!=player_skin && mappa->pos(x,y+1)!=bomb_exp && mappa->pos(x,y+1)!=item_l && mappa->pos(x,y+1)!=item_r && mappa->pos(x,y+1)!=item_n && mappa->pos(x,y+1)!=item_t && mappa->pos(x,y+1)!=item_p) ))
                || dir==-1) {
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
            if (mappa->pos(x,y)==bomb_exp
                || mappa->pos(x,y)==item_l
                || mappa->pos(x,y)==item_r
                || mappa->pos(x,y)==item_n
                || mappa->pos(x,y)==item_t
                || mappa->pos(x,y)==item_p) {
                }
            else {
                mappa->cambia(x,y,base_en);
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
        x=rand()%30+10;
        y=rand()%19+1;
    }while (mappa->pos(x,y)!=vuoto);
    aspetto=adv_enemy_vuoto;
    mappa->cambia(x,y,adv_enemy_vuoto);
    velocita=12;
}

void advanced_enemy::move(Player *pl) {
    if (tick>=velocita) {
        if (pl->get_coordinata_x()!=x || pl->get_coordinata_y()!=y) {
            //se era su una bomba/item
            if (mappa->pos(x,y)==bomb_exp
                || mappa->pos(x,y)==item_l
                || mappa->pos(x,y)==item_r
                || mappa->pos(x,y)==item_n
                || mappa->pos(x,y)==item_t
                || mappa->pos(x,y)==item_p) {
                }
            //se è sul vuoto
            else if (mappa->pos(x,y)==adv_enemy_vuoto) {
                mappa->cambia(x,y,vuoto);
            }

            //se è su un muro distruttibile
            else if (mappa->pos(x,y)==adv_enemy_muro) {
                mappa->cambia(x,y,muro);
            }

            //se è su un muro indistruttibile
            else if (mappa->pos(x,y)==adv_enemy_muro_ind) {
                mappa->cambia(x,y,muro_ind);
            }
            //se era sul player
            else if (pl->get_coordinata_x()==x && pl->get_coordinata_y()==y) {
                mappa->cambia(x,y,player_skin);
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

            //se è su una bomba/item
            if (mappa->pos(x,y)==bomb_exp
                || mappa->pos(x,y)==item_l
                || mappa->pos(x,y)==item_r
                || mappa->pos(x,y)==item_n
                || mappa->pos(x,y)==item_t
                || mappa->pos(x,y)==item_p) {
                }

            //se è sul vuoto
            else if (mappa->pos(x,y)==vuoto) {
                mappa->cambia(x,y,adv_enemy_vuoto);
            }

            //se è su un muro distruttibile
            else if (mappa->pos(x,y)==muro) {
                mappa->cambia(x,y,adv_enemy_muro);
            }

            //se è su un muro indistruttibile
            else if (mappa->pos(x,y)==muro_ind) {
                mappa->cambia(x,y,adv_enemy_muro_ind);
            }

            //se è sul player
            else if (mappa->pos(x,y)==player_skin) {
                mappa->cambia(x,y,adv_enemy_vuoto);
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
