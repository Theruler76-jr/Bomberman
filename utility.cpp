#include "utility.h"

#include <iostream>

Item::Item(Map *_mappa, Player *_pl) {
    mappa=_mappa;
    pl=_pl;
    do {
        x=rand()%39+1;
        y=rand()%19+1;
    }while (mappa->pos(x,y)!='m');
}

int Item::get_x() {
    return(x);
}

int Item::get_y() {
    return(y);
}



raggio_bomba::raggio_bomba(Map *_mappa, Player *_pl) : Item(_mappa, _pl){
    aspetto='R';
    mappa->cambia(x,y,'R');
}

void raggio_bomba::applica_effetto() {
   pl->cambia_moltiplicatore_bombe(1);
}

nuova_vita::nuova_vita(Map *_mappa, Player *_pl) : Item(_mappa, _pl){
    aspetto='L';
    mappa->cambia(x,y,'L');
}

void nuova_vita::applica_effetto() {
    pl->cambia_numero_vite(1);
}

num_bombe::num_bombe(Map *_mappa, Player *_pl) : Item(_mappa, _pl){
    aspetto='N';
    mappa->cambia(x,y,'N');
}

void num_bombe::applica_effetto() {
    pl->cambia_numero_bombe(1);
}

