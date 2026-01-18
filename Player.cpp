#include "Player.h"


 Player :: Player (int c_x, int c_y, int n_v, int n_b) {
     coordinata_x = c_x;
     coordinata_y = c_y;
     numero_vite = n_v;
     numero_bombe = 1;
     moltiplicatore_bombe = 1;
}


int Player :: get_coordinata_x () {
     return coordinata_x;
}

int Player :: get_coordinata_y () {
    return coordinata_y;
}

bool Player :: cambia_numero_vite (int x) {
    if (numero_vite + x >= 0) {
        numero_vite += x;
        return true;
    }
     return false;
}

void Player :: move_x (int change) {
    coordinata_x += change;
}

void Player :: move_y (int change) {
    coordinata_y += change;
}

int Player :: get_numero_vite () {
     return numero_vite;
 }

void Player :: cambia_numero_bombe(int x) {
    numero_bombe += x;
}

void Player::cambia_moltiplicatore_bombe(int x) {
    moltiplicatore_bombe += x;
}

int Player::get_moltiplicatore_bombe() {
    return moltiplicatore_bombe;
}
