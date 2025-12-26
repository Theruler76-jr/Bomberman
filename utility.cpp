#include "utility.h"

#include <iostream>

Item::Item(Map *_mappa, Player *_pl, Bomb *_b) {
    mappa=_mappa;
    pl=_pl;
    b=_b;
    preso=false;
    do {
        x=rand()%39+1;
        y=rand()%19+1;
    }while (mappa->pos(x,y)!='m');
}

void Item::prendi() {
    preso=true;
}

raggio_bomba::raggio_bomba(Map *_mappa, Player *_pl, Bomb *_b) : Item(_mappa, _pl, _b){
    aspetto='R';
    if (preso) {
        b->cambia_moltiplicatore_esplosione(2);
    }
}

nuova_vita::nuova_vita(Map *_mappa, Player *_pl, Bomb *_b) : Item(_mappa, _pl, _b){
    if (preso) {
        pl->cambia_numero_vite(1);
    }
}

num_bombe::num_bombe(Map *_mappa, Player *_pl, Bomb *_b) : Item(_mappa, _pl, _b){
    pl->cambia_numero_bombe(1);
}


