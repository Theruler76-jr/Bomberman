#include "Bomb.h"
#include "enemy.h"
#include "game.h"
#include "Map.h"
#include "Player.h"

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

int Bomb :: get_activation_time () {
    return activation_time;
}

int Bomb :: esplodi (Map &mappa, Player &Giocatore, int &score, enemy_list* &lista_nemici) {
    int enemy_killed = 0, coord_x_destra = coordinata_x, coord_x_sinistra = coordinata_x, coord_y_sopra = coordinata_y, coord_y_sotto = coordinata_y;
    bool muro_dx = false, muro_sx = false, muro_up = false, muro_dw = false;

    for (int shift = 0; shift <= moltiplicatore_esplosione; shift ++) {
        //casella a sinistra
        if (!muro_sx) {
            switch (mappa.pos(coord_x_sinistra, coordinata_y)) {
                case 'm':
                    mappa.cambia(coord_x_sinistra, coordinata_y,'v');
                    break;
                case 'R':
                    mappa.cambia(coord_x_sinistra, coordinata_y,'r');
                    break;
                case 'L':
                    mappa.cambia(coord_x_sinistra, coordinata_y,'l');
                    break;
                case 'N':
                    mappa.cambia(coord_x_sinistra, coordinata_y,'n');
                    break;
                case 'P':
                    mappa.cambia(coord_x_sinistra, coordinata_y,'p');
                    break;
                case 'T':
                    mappa.cambia(coord_x_sinistra, coordinata_y,'t');
                    break;
                case '#':
                    score += score_per_enemy;
                    lista_nemici = rimuovi_nemico(lista_nemici, coord_x_sinistra, coordinata_y);
                    mappa.cambia(coord_x_sinistra, coordinata_y,'v');
                    enemy_killed++;
                    break;
                case '%':
                    score += score_per_enemy + 10;
                    lista_nemici = rimuovi_nemico(lista_nemici, coord_x_sinistra, coordinata_y);
                    mappa.cambia(coord_x_sinistra, coordinata_y,'v');
                    enemy_killed++;
                    break;
                case 'x':
                    lista_nemici = rimuovi_nemico(lista_nemici, coord_x_sinistra, coordinata_y);
                    mappa.cambia(coord_x_sinistra, coordinata_y,'v');
                    enemy_killed++;
                    break;
                case 'z':
                    lista_nemici = rimuovi_nemico(lista_nemici, coord_x_sinistra, coordinata_y);
                    mappa.cambia(coord_x_sinistra, coordinata_y,'v');
                    enemy_killed++;
                    break;
                case 'I':
                    muro_sx = true;
                    break;
                default:
                    break;
            }

            if (Giocatore.get_coordinata_x() == coord_x_sinistra && Giocatore.get_coordinata_y() == coordinata_y) {
                Giocatore.cambia_numero_vite(-1);
                Giocatore.immunity();
            }
        }

        //casella a destra
        if (!muro_dx) {
            switch (mappa.pos(coord_x_destra, coordinata_y)) {
                case 'm':
                    mappa.cambia(coord_x_destra, coordinata_y,'v');
                    break;
                case 'R':
                    mappa.cambia(coord_x_destra, coordinata_y,'r');
                    break;
                case 'L':
                    mappa.cambia(coord_x_destra, coordinata_y,'l');
                    break;
                case 'N':
                    mappa.cambia(coord_x_destra, coordinata_y,'n');
                    break;
                case 'P':
                    mappa.cambia(coord_x_destra, coordinata_y,'p');
                    break;
                case 'T':
                    mappa.cambia(coord_x_destra, coordinata_y,'t');
                    break;
                case '#':
                    score += score_per_enemy;
                    lista_nemici = rimuovi_nemico(lista_nemici, coord_x_destra, coordinata_y);
                    mappa.cambia(coord_x_destra, coordinata_y,'v');
                    enemy_killed++;
                    break;
                case '%':
                    score += score_per_enemy + 10;
                    lista_nemici = rimuovi_nemico(lista_nemici, coord_x_destra, coordinata_y);
                    mappa.cambia(coord_x_destra, coordinata_y,'v');
                    enemy_killed++;
                    break;
                case 'x':
                    lista_nemici = rimuovi_nemico(lista_nemici, coord_x_destra, coordinata_y);
                    mappa.cambia(coord_x_destra, coordinata_y,'v');
                    enemy_killed++;
                    break;
                case 'z':
                    lista_nemici = rimuovi_nemico(lista_nemici, coord_x_destra, coordinata_y);
                    mappa.cambia(coord_x_destra, coordinata_y,'v');
                    enemy_killed++;
                    break;
                case 'I':
                    muro_dx = true;
                    break;
                default:
                    break;
            }

            if (Giocatore.get_coordinata_x() == coord_x_destra && Giocatore.get_coordinata_y() == coordinata_y) {
                Giocatore.cambia_numero_vite(-1);
                Giocatore.immunity();
            }
        }
        //casella sopra
        if (!muro_up) {
            switch (mappa.pos(coordinata_x, coord_y_sopra)) {
                case 'm':
                    mappa.cambia(coordinata_x, coord_y_sopra,'v');
                    break;
                case 'R':
                    mappa.cambia(coordinata_x, coord_y_sopra,'r');
                    break;
                case 'L':
                    mappa.cambia(coordinata_x, coord_y_sopra,'l');
                    break;
                case 'N':
                    mappa.cambia(coordinata_x, coord_y_sopra,'n');
                    break;
                case 'P':
                    mappa.cambia(coordinata_x, coord_y_sopra,'p');
                    break;
                case 'T':
                    mappa.cambia(coordinata_x, coord_y_sopra,'t');
                    break;
                case '#':
                    score += score_per_enemy;
                    lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x, coord_y_sopra);
                    mappa.cambia(coordinata_x, coord_y_sopra,'v');
                    enemy_killed++;
                    break;
                case '%':
                    score += score_per_enemy + 10;
                    lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x, coord_y_sopra);
                    mappa.cambia(coordinata_x, coord_y_sopra,'v');
                    enemy_killed++;
                    break;
                case 'x':
                    lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x, coord_y_sopra);
                    mappa.cambia(coordinata_x, coord_y_sopra,'v');
                    enemy_killed++;
                    break;
                case 'z':
                    lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x, coord_y_sopra);
                    mappa.cambia(coordinata_x, coord_y_sopra,'v');
                    enemy_killed++;
                    break;
                case 'I':
                    muro_up = true;
                    break;
                default:
                    break;
        }

            if (Giocatore.get_coordinata_x() == coordinata_x && Giocatore.get_coordinata_y() == coord_y_sopra) {
                Giocatore.cambia_numero_vite(-1);
                Giocatore.immunity();
            }
        }
        //casella sotto
        if (!muro_dw) {
            switch (mappa.pos(coordinata_x, coord_y_sotto)) {
                case 'm':
                    mappa.cambia(coordinata_x, coord_y_sotto,'v');
                    break;
                case 'R':
                    mappa.cambia(coordinata_x, coord_y_sotto,'r');
                    break;
                case 'L':
                    mappa.cambia(coordinata_x, coord_y_sotto,'l');
                    break;
                case 'N':
                    mappa.cambia(coordinata_x, coord_y_sotto,'n');
                    break;
                case 'P':
                    mappa.cambia(coordinata_x, coord_y_sotto,'p');
                    break;
                case 'T':
                    mappa.cambia(coordinata_x, coord_y_sotto,'t');
                    break;
                case '#':
                    score += score_per_enemy;
                    lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x, coord_y_sotto);
                    mappa.cambia(coordinata_x, coord_y_sotto,'v');
                    enemy_killed++;
                    break;
                case '%':
                    score += score_per_enemy + 10;
                    lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x, coord_y_sotto);
                    mappa.cambia(coordinata_x, coord_y_sotto,'v');
                    enemy_killed++;
                    break;
                case 'x':
                    lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x, coord_y_sotto);
                    mappa.cambia(coordinata_x, coord_y_sotto,'v');
                    enemy_killed++;
                    break;
                case 'z':
                    lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x, coord_y_sotto);
                    mappa.cambia(coordinata_x, coord_y_sotto,'v');
                    enemy_killed++;
                    break;
                case 'I':
                    muro_dw = true;
                    break;
                default:
                    break;
        }

            if (Giocatore.get_coordinata_x() == coordinata_x && Giocatore.get_coordinata_y() == coord_y_sotto) {
                Giocatore.cambia_numero_vite(-1);
                Giocatore.immunity();
            }
        }
        //aggiorno le posizioni
        coord_x_destra ++;
        coord_x_sinistra --;
        coord_y_sopra ++;
        coord_y_sotto --;
    }
    //cancello la bomba
    if (Giocatore.get_coordinata_x() != coordinata_x || Giocatore.get_coordinata_y() != coordinata_y)
        mappa.cambia(coordinata_x,coordinata_y,'v');
    else
        mappa.cambia(coordinata_x,coordinata_y,player_skin);

    Giocatore.cambia_numero_bombe_schierate(-1);
    return enemy_killed;

}