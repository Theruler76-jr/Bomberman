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
    enemy(Map *_mappa);
    int get_x();
    int get_y();
    void stamp(WINDOW *win, int start_x, int start_y);
    void remove_old(WINDOW *win, int start_x, int start_y);
};

class base_enemy : public enemy {
protected:
    int dir;
public:
    base_enemy(Map *_mappa);
    void move();
};

class advanced_enemy : public enemy {
public:
    advanced_enemy(Map *_mappa);
    void move(Player x);
};
