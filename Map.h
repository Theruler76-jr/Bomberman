#pragma once
#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

//Classe mappa, è una matrice 20*40, i muri indistruttibili sono segnati come I,
//                                   gli altri come m
//                                   e gli spazi vuoti come c
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
    void stamp (WINDOW *win);

    //restituisce cosa è presente nella mappa in una determinata posizione
    char position (int x, int y) {
        return(map[y][x]);
    }
};