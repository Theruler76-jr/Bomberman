#include "Player.h"


 Player :: Player (int c_x, int c_y, int n_v, int n_b) {
     coordinata_x = c_x;
     coordinata_y = c_y;
     numero_vite = n_v;
}


int Player :: get_coordinata_x () {
     return coordinata_x;
}

int Player :: get_coordinata_y () {
    return coordinata_y;
}

bool Player :: cambia_numero_vite (int x) {
    numero_vite += x;
    if (numero_vite > 0)
        return true;
    return false;
}

void Player :: move_x (int x) {
    coordinata_x += x;
}

void Player :: move_y (int x) {
    coordinata_y += x;
}

int Player :: get_numero_vite () {
     return numero_vite;
 }