#pragma once

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

char game_loop(WINDOW *win);
struct Level;
Level* find_last (Level* current); //Funzione ausiliaria di push_level
Level* push_level (Level* head_level, int level_number); //Funzione ausiliaria di Levels_initializer
Level* levels_initializer (Level *head_level); //Con questa funzione creo la lista bidirezionale di tutti i livelli
Level* remove_level (Level* current_level); //con questa funzione si elimina il livello passato per parametro e ritorna il livello successivo