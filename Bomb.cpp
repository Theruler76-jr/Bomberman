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
    int enemy_killed = 0;
    int x_directions [5] = {0, 0, 1, -1, 0};
    int y_directions [5] = {0, -1, 0, 0, 1};
    bool stop [5] = {false, false, false, false};

    for (int i = 1; i <= moltiplicatore_esplosione; i++) {
        for (int j = 0; j < 5; j++) {
            if (!stop[j]) {
                switch (mappa.pos(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i)) {
                    case muro:
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,vuoto);
                        score += 5;
                        break;
                    case item_wall_R:
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,item_r);
                        score += 5;
                        break;
                    case item_wall_L:
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,item_l);
                        score += 5;
                        break;
                    case item_wall_N:
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,item_n);
                        score += 5;
                        break;
                    case item_wall_P:
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,item_p);
                        score += 5;
                        break;
                    case item_wall_T:
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,item_t);
                        score += 5;
                        break;
                    case base_en:
                        score += score_per_enemy;
                        lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i);
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,vuoto);
                        enemy_killed++;
                        break;
                    case adv_enemy_vuoto:
                        score += score_per_enemy + 10;
                        lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i);
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,vuoto);
                        enemy_killed++;
                        break;
                    case adv_enemy_muro:
                        lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i);
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,vuoto);
                        enemy_killed++;
                        break;
                    case adv_enemy_muro_ind:
                        lista_nemici = rimuovi_nemico(lista_nemici, coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i);
                        mappa.cambia(coordinata_x + x_directions[j] * i, coordinata_y + y_directions[j] * i,vuoto);
                        enemy_killed++;
                        break;
                    case muro_ind:
                        stop[j] = true;
                        break;
                    default:
                        break;
                }

                if (Giocatore.get_coordinata_x() == coordinata_x + x_directions[j] * i && Giocatore.get_coordinata_y() == coordinata_y + y_directions[j] * i) {
                    Giocatore.cambia_numero_vite(-1);
                    Giocatore.immunity();
                }
            }
        }
    }
    //cancello la bomba
    if (Giocatore.get_coordinata_x() != coordinata_x || Giocatore.get_coordinata_y() != coordinata_y)
        mappa.cambia(coordinata_x,coordinata_y,vuoto);
    else
        mappa.cambia(coordinata_x,coordinata_y,player_skin);

    Giocatore.cambia_numero_bombe_schierate(-1);
    return enemy_killed;
}