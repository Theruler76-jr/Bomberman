# pragma once
#include "Map.h"
#include "Player.h"
#include "Bomb.h"

class Item {
protected:
    int x,y;
    char aspetto;
    Map *mappa;
    Player *pl;
    Bomb *b;
    bool preso;
public:
    Item(Map *_mappa, Player *_pl, Bomb *_b);
    void prendi();
};

class raggio_bomba :Item {
public:
    raggio_bomba(Map *_mappa, Player *_pl, Bomb *_b);
};

class nuova_vita :Item {
public:
    nuova_vita(Map *_mappa, Player *_pl, Bomb *_b);
};

class num_bombe :Item {
    num_bombe(Map *_mappa, Player *_pl, Bomb *_b);
};