#pragma once
#include "Map.h"
#include "Player.h"

class enemy {
protected:
    int x,y;
    int tick, velocità;
    char aspetto;
    Map *mappa;
public:
    enemy(char asp, Map *_mappa);
    int get_x();
    int get_y();
};

class base_enemy : public enemy {
protected:
    int dir;
public:
    base_enemy(char asp, Map *_mappa);
    void move();
};

class advanced_enemy : public enemy {
public:
    advanced_enemy(char asp, Map *_mappa);
    void move(Player x);
};
