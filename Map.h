#pragma once

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif


//variabili mappa

const char muro_ind = 'I';
const char muro = 'm';
const char vuoto = 'v';
const char item_wall_R = 'R';
const char item_wall_L = 'L';
const char item_wall_N = 'N';
const char item_wall_T = 'T';
const char item_wall_P = 'P';
const char item_r = 'r';
const char item_l = 'l';
const char item_n = 'n';
const char item_t = 't';
const char item_p = 'p';
const char base_en = '#';
const char adv_enemy_vuoto = '%';
const char adv_enemy_muro = 'x';
const char adv_enemy_muro_ind = 'z';

//Classe mappa, è una matrice 21*41
class Map {
protected:
    int row=21, col=41;
    char map[21][41];
public:
    //construttore, initializza i muri indistruttibili
    Map();

    //crea la mappa di un determinato livello in input
    void livello (int lv);

    //stampa a schermo la mappa completa
    void stamp (WINDOW *win, int x_start, int y_start);

    //restituisce cosa è presente nella mappa in una determinata posizione
    char pos (int x, int y);

    //cambia una casella
    void cambia(int x, int y, char nuovo);
};