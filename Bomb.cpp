#include "Bomb.h"

Bomb :: Bomb() {}


Bomb :: Bomb (int c_x, int c_y,unsigned int time_spawn, int m_e) {
    coordinata_x = c_x;
    coordinata_y = c_y;
    moltiplicatore_esplosione = m_e;
    activation_time = time_spawn;
}

int Bomb :: get_coordinata_x () {
    return coordinata_x;
}

int Bomb :: get_coordinata_y () {
    return coordinata_y;
}

void Bomb :: cambia_moltiplicatore_esplosione (int change) {
    moltiplicatore_esplosione = change;
}

int Bomb :: get_activation_time () {
    return activation_time;
}

void Bomb :: esplodi (Map &mappa, Player &Giocatore) {

    for (int x_off = -moltiplicatore_esplosione; x_off <= moltiplicatore_esplosione; x_off++) {
        switch (mappa.pos(coordinata_x + x_off, coordinata_y)) {
        case 'm':
            mappa.cambia(coordinata_x + x_off, coordinata_y,'v');
            break;
        case 'R':
            mappa.cambia(coordinata_x + x_off, coordinata_y,'r');
            break;
        case 'L':
            mappa.cambia(coordinata_x + x_off, coordinata_y,'l');
            break;
        case 'N':
            mappa.cambia(coordinata_x + x_off, coordinata_y,'n');
            break;
        case player_skin:
            Giocatore.cambia_numero_vite(-1);
            break;
        }
    }

    for (int y_off = -moltiplicatore_esplosione; y_off <= moltiplicatore_esplosione; y_off++) {
        switch (mappa.pos(coordinata_x, coordinata_y + y_off)) {
        case 'm':
            mappa.cambia(coordinata_x, coordinata_y + y_off,'v');
            break;
        case 'R':
            mappa.cambia(coordinata_x, coordinata_y + y_off,'r');
            break;
        case 'L':
            mappa.cambia(coordinata_x, coordinata_y + y_off,'l');
            break;
        case 'N':
            mappa.cambia(coordinata_x, coordinata_y + y_off,'n');
            break;
        case player_skin:
            Giocatore.cambia_numero_vite(-1);
            break;
        }
    }

    //controllo se mina e giocatore sono nello stesso posto
    if (Giocatore.get_coordinata_x() == coordinata_x && Giocatore.get_coordinata_y() == coordinata_y)
        Giocatore.cambia_numero_vite(-1);

    //cancello la bomba
    if (Giocatore.get_coordinata_x() != coordinata_x || Giocatore.get_coordinata_y() != coordinata_y)
        mappa.cambia(coordinata_x,coordinata_y,'v');
    else
        mappa.cambia(coordinata_x,coordinata_y,player_skin);

}
