#include "utility.h"
#include "game.h"

#include <iostream>

Item::Item(Map *_mappa, Player *_pl) {
    mappa=_mappa;
    pl=_pl;
    do {
        x=rand()%39+1;
        y=rand()%19+1;
    }while (mappa->pos(x,y)!=muro);
}

int Item::get_x() {
    return(x);
}

int Item::get_y() {
    return(y);
}

char Item::get_aspetto() { //restituisce lettera piccola
    if (aspetto==item_wall_R) {
        return(item_r);
    }
    if (aspetto==item_wall_L) {
        return(item_l);
    }
    if (aspetto==item_wall_N) {
        return(item_n);
    }
    if (aspetto==item_wall_P) {
        return(item_p);
    }
    if (aspetto==item_wall_T) {
        return(item_t);
    }
    return('k'); //caso base mai usato
}

Item::~Item() {

}

raggio_bomba::raggio_bomba(Map *_mappa, Player *_pl) : Item(_mappa, _pl){
    aspetto=item_wall_R;
    mappa->cambia(x,y,item_wall_R);
}

void raggio_bomba::applica_effetto(Level *lv, int &score) {
   pl->cambia_moltiplicatore_bombe(1);
}

nuova_vita::nuova_vita(Map *_mappa, Player *_pl) : Item(_mappa, _pl){
    aspetto=item_wall_L;
    mappa->cambia(x,y,item_wall_L);
}

void nuova_vita::applica_effetto(Level *lv, int &score) {
    pl->cambia_numero_vite(1);
}

num_bombe::num_bombe(Map *_mappa, Player *_pl) : Item(_mappa, _pl){
    aspetto=item_wall_N;
    mappa->cambia(x,y,item_wall_N);
}

void num_bombe::applica_effetto(Level *lv, int &score) {
    pl->cambia_numero_bombe(1);
}

add_tempo::add_tempo(Map *_mappa, Player *_pl) : Item(_mappa,_pl){
    aspetto=item_wall_T;
    mappa->cambia(x,y,item_wall_T);
}

void add_tempo::applica_effetto(Level *lv, int &score) {
    (lv->time_left)+=60;
}

add_punti::add_punti(Map *_mappa, Player *_pl) : Item(_mappa, _pl){
    aspetto=item_wall_P;
    mappa->cambia(x,y,item_wall_P);
}

void add_punti::applica_effetto(Level *lv, int &score) {
    score+=50;
}


