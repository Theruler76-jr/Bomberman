#pragma once
#include "Map.h"
#include "Player.h"

class enemy {
protected:
    int x,y;
    int tick, velocita;
    char aspetto;
    Map *mappa;
public:
    enemy(Map *_mappa=NULL);
    int get_x();
    int get_y();
    virtual void move()=0;
};

class base_enemy : public enemy {
protected:
    int dir;
public:
    base_enemy(Map *_mappa=NULL);
    void move();
};

class advanced_enemy : public enemy {
public:
    advanced_enemy(Map *_mappa=NULL);
    void move();
    void move(Player *x);
};
