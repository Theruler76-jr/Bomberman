#pragma once

class Bomb {
protected:
    int coordinata_x;
    int coordinata_y;
    unsigned int moltiplicatore_esplosione;
public:
    Bomb (int c_x, int c_y, int m_e = 1);
    int get_coordinata_x ();
    int get_coordinata_y ();
    void cambia_moltiplicatore_esplosione (unsigned int); //cambia del tutto, non aggiunge ne sottrae
    void esplodi ();
};


