#include "Bomb.h"


Bomb :: Bomb (int c_x, int c_y, int m_e) {
    coordinata_x = c_x;
    coordinata_y = c_y;
    moltiplicatore_esplosione = m_e;
}

int Bomb :: get_coordinata_x () {
    return coordinata_x;
}

int Bomb :: get_coordinata_y () {
    return coordinata_y;
}

void Bomb :: cambia_moltiplicatore_esplosione (unsigned int change) {
    moltiplicatore_esplosione = change;
}

void Bomb :: esplodi () {
    //to do
}