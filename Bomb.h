#pragma once
#include "Map.h"
#include "Player.h"
#include "game.h"

const char bomb_skin = '$';

struct enemy_list;

class Bomb {
protected:
    int coordinata_x;
    int coordinata_y;
    int moltiplicatore_esplosione;
    unsigned int activation_time;

public:
    Bomb();
    Bomb (int c_x, int c_y, unsigned int time_spawn, int m_e = 1);
    int get_coordinata_x ();
    int get_coordinata_y ();
    int get_activation_time (); //restituisce quando e' stata piazzata la bomba (time globale di quando é iniziata l'esecuzione)
    void esplodi (Map &mappa, Player &Giocatore, int &score, enemy_list *&lista_nemici); // fa esplodere la bomba e riduce le vite del giocatore in caso venisse colpito
};