# pragma once
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "game.h"

class Item {
protected:
    int x,y;
    char aspetto;
    Map *mappa;
    Player *pl;
public:
    Item(Map *_mappa=NULL, Player *_pl=NULL);
    int get_x();
    int get_y();
    virtual ~Item()=0;
    virtual void applica_effetto(Level *lv, int &score)=0;
    char get_aspetto();
};

class raggio_bomba : public Item {
public:
    raggio_bomba(Map *_mappa, Player *_pl);
    void applica_effetto(Level *lv, int &score);
};

class nuova_vita : public Item {
public:
    nuova_vita(Map *_mappa, Player *_pl);
    void applica_effetto(Level *lv, int &score);

};

class num_bombe : public Item {
public:
    num_bombe(Map *_mappa, Player *_pl);
    void applica_effetto(Level *lv, int &score);
};

class add_tempo : public Item{
public:
    add_tempo(Map *_mappa, Player *_pl);
    void applica_effetto(Level *lv, int &score);
};

class add_punti : public Item {
public:
    add_punti(Map *_mappa, Player *_pl);
    void applica_effetto(Level *lv, int &score);
};
