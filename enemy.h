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
    enemy(int vel, char asp, Map *_mappa);
    int get_x();
    int get_y();
    void stamp(WINDOW *win);
};

class base_enemy : public enemy {
protected:
    int dir;
public:
    base_enemy(int vel, char asp, Map *_mappa);
    void move();
};

class advanced_enemy : public enemy {
public:
    void move(Player x);
};
