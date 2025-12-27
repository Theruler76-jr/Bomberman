#include "utility.h"

#include <iostream>

Item::Item(Map *_mappa, Player *_pl, Bomb *_b) {
    mappa=_mappa;
    pl=_pl;
    b=_b;
    do {
        x=rand()%39+1;
        y=rand()%19+1;
    }while (mappa->pos(x,y)!='m');
}

raggio_bomba::raggio_bomba(Map *_mappa, Player *_pl, Bomb *_b) : Item(_mappa, _pl, _b){
    aspetto='R';

}

void raggio_bomba::applica_effetto() {
    b->cambia_moltiplicatore_esplosione(2);
}

nuova_vita::nuova_vita(Map *_mappa, Player *_pl, Bomb *_b) : Item(_mappa, _pl, _b){
    aspetto='L';
}

void nuova_vita::applica_effetto() {
    pl->cambia_numero_vite(1);
}

num_bombe::num_bombe(Map *_mappa, Player *_pl, Bomb *_b) : Item(_mappa, _pl, _b){
    aspetto='N';
}

void num_bombe::applica_effetto() {
    pl->cambia_numero_bombe(1);
}

