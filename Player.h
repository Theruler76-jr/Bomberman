#pragma once


class Player {
protected:
    int coordinata_x;
    int coordinata_y;
    int numero_vite;
    int numero_bombe;
    int bombe_schierate;
    int moltiplicatore_bombe;
    bool hittable;

public:
    Player (int c_x = 1, int c_y = 1, int n_v = 3, int m_b = 1); //da decidere il numero di vite con cui partire
    int get_coordinata_x ();
    int get_coordinata_y ();
    bool cambia_numero_vite (int x); // Ritorna 1 se non é morto, 0 se ha finito le vite. Per decrementare bisogna passare un int negativo
    void move_x (int x);
    void move_y (int x);
    int get_numero_vite ();
    void cambia_numero_bombe (int x);
    void cambia_moltiplicatore_bombe (int x);
    int get_moltiplicatore_bombe ();
    int get_numero_bombe ();
    int get_bombe_schierate ();
    void cambia_numero_bombe_schierate (int x);
    void immunity ();
    void vulnerable ();
};