#pragma once
#include "Player.h"
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
void write_score (int score); //scrive il punteggio attuale del giocatore
void write_lives (Player giocatore); //scrive il numero di vite rimanenti al giocatore
void write_level (int number); //scrive il numero di livello in cui si trova il giocatore
Level* next_level (Level *current_level); //porta il giocatore al livello successivo, non succede niente se é l'ultimo livello
Level* previous_level (Level *current_level); //porta il giocatore al livello precedente, non succede niente se é il primo livello