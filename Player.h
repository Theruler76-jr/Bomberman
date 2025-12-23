#pragma once

class Player {
protected:
    int coordinata_x;
    int coordinata_y;
    int numero_vite;
    int numero_bombe;
public:
    Player (int c_x = 1, int c_y = 1, int n_v = 3, int n_b = 0); //da decidere il numero di vite con cui partire
    int get_coordinata_x ();
    int get_coordinata_y ();
    bool cambia_numero_vite (int x); // Ritorna 1 se non é morto, 0 se ha finito le vite. Per decrementare bisogna passare un int negativo
    void move_x (int x);
    void move_y (int x);
    int get_numero_vite ();
};

