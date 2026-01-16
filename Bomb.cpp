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
    if (mappa.pos(coordinata_x,coordinata_y+moltiplicatore_esplosione) == 'm')
        mappa.cambia(coordinata_x,coordinata_y+moltiplicatore_esplosione,'v');
    if (mappa.pos(coordinata_x+moltiplicatore_esplosione,coordinata_y) == 'm')
        mappa.cambia(coordinata_x+moltiplicatore_esplosione,coordinata_y,'v');
    if (mappa.pos(coordinata_x,coordinata_y-moltiplicatore_esplosione) == 'm')
        mappa.cambia(coordinata_x,coordinata_y-moltiplicatore_esplosione,'v');
    if (mappa.pos(coordinata_x-moltiplicatore_esplosione,coordinata_y) == 'm')
        mappa.cambia(coordinata_x-moltiplicatore_esplosione,coordinata_y,'v');

    //gestisco item sotto i muri
    if (mappa.pos(coordinata_x,coordinata_y+moltiplicatore_esplosione) == 'R')
        mappa.cambia(coordinata_x,coordinata_y+moltiplicatore_esplosione,'r');
    if (mappa.pos(coordinata_x+moltiplicatore_esplosione,coordinata_y) == 'R')
        mappa.cambia(coordinata_x+moltiplicatore_esplosione,coordinata_y,'r');
    if (mappa.pos(coordinata_x,coordinata_y-moltiplicatore_esplosione) == 'R')
        mappa.cambia(coordinata_x,coordinata_y-moltiplicatore_esplosione,'r');
    if (mappa.pos(coordinata_x-moltiplicatore_esplosione,coordinata_y) == 'R')
        mappa.cambia(coordinata_x-moltiplicatore_esplosione,coordinata_y,'r');

    if (mappa.pos(coordinata_x,coordinata_y+moltiplicatore_esplosione) == 'L')
        mappa.cambia(coordinata_x,coordinata_y+moltiplicatore_esplosione,'l');
    if (mappa.pos(coordinata_x+moltiplicatore_esplosione,coordinata_y) == 'L')
        mappa.cambia(coordinata_x+moltiplicatore_esplosione,coordinata_y,'l');
    if (mappa.pos(coordinata_x,coordinata_y-moltiplicatore_esplosione) == 'L')
        mappa.cambia(coordinata_x,coordinata_y-moltiplicatore_esplosione,'l');
    if (mappa.pos(coordinata_x-moltiplicatore_esplosione,coordinata_y) == 'L')
        mappa.cambia(coordinata_x-moltiplicatore_esplosione,coordinata_y,'l');

    if (mappa.pos(coordinata_x,coordinata_y+moltiplicatore_esplosione) == 'N')
        mappa.cambia(coordinata_x,coordinata_y+moltiplicatore_esplosione,'n');
    if (mappa.pos(coordinata_x+moltiplicatore_esplosione,coordinata_y) == 'N')
        mappa.cambia(coordinata_x+moltiplicatore_esplosione,coordinata_y,'n');
    if (mappa.pos(coordinata_x,coordinata_y-moltiplicatore_esplosione) == 'N')
        mappa.cambia(coordinata_x,coordinata_y-moltiplicatore_esplosione,'n');
    if (mappa.pos(coordinata_x-moltiplicatore_esplosione,coordinata_y) == 'N')
        mappa.cambia(coordinata_x-moltiplicatore_esplosione,coordinata_y,'n');

    //La seguente pier-codata é frutto del fatto che a 4 condizioni diverse corrisponde la stessa azione
    if (mappa.pos(coordinata_x,coordinata_y+moltiplicatore_esplosione) == player_skin || mappa.pos(coordinata_x+moltiplicatore_esplosione,coordinata_y) == player_skin || mappa.pos(coordinata_x,coordinata_y-moltiplicatore_esplosione) == player_skin || mappa.pos(coordinata_x-moltiplicatore_esplosione,coordinata_y) == player_skin || (Giocatore.get_coordinata_x() == coordinata_x && Giocatore.get_coordinata_y() == coordinata_y))
        Giocatore.cambia_numero_vite(-1);

    //cancello la bomba
    if (Giocatore.get_coordinata_x() != coordinata_x || Giocatore.get_coordinata_y() != coordinata_y)
        mappa.cambia(coordinata_x,coordinata_y,'v');
    else
        mappa.cambia(coordinata_x,coordinata_y,player_skin);

}
