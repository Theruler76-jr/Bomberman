#pragma once
#include "Player.h"
#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include <ctime>

const int numero_livelli = 5; //questa dichiarazione é temporanea se si vuole rimuovere bisogna accordarsi su un numero
const char player_skin = '@'; //così se vogliamo cambiare la skin lo si può fare nel chill
const int time_per_level = 200;

char game_loop(WINDOW *win);
struct  bomb_list;
struct Level;

void write_score (int score, WINDOW* win); //scrive il punteggio attuale del giocatore
void write_lives (Player giocatore, WINDOW *win); //scrive il numero di vite rimanenti al giocatore
void write_level (int number,WINDOW *win); //scrive il numero di livello in cui si trova il giocatore
void write_time_left (Level *current_level,WINDOW *win); //scrive il numero di secondi rimasti per ogni livello
void print_routine (Level* current_level, Player Giocatore, int score, WINDOW *win); //stampa tutte le informazioni a schermo a ogni ciclo

Level* find_last (Level* current); //Funzione ausiliaria di push_level
Level* push_level (Level* head_level, int level_number); //Funzione ausiliaria di Levels_initializer
Level* levels_initializer (Level *head_level); //Con questa funzione creo la lista bidirezionale di tutti i livelli
Level* remove_level (Level* current_level); //con questa funzione si elimina il livello passato per parametro e ritorna il livello successivo
Level* next_level (Level *current_level); //porta il giocatore al livello successivo, non succede niente se é l'ultimo livello
Level* previous_level (Level *current_level); //porta il giocatore al livello precedente, non succede niente se é il primo livello
Level* move_player (char direction, Level* current_level, Player &Giocatore, int &score);//muove il player controllando di non star andando nei muri

bomb_list* add_bomb (bomb_list *head, int coord_x, int coord_y, unsigned int time_placing, int molt_explosion, Map &map); //aggiunge una bomba alla lista di bombe del livello
bomb_list* get_last (bomb_list *element); //funzione ausiliaria di add_bomb
bomb_list* check_bomb_status (bomb_list *&head, int time, Player &Giocatore, Map &map); //controlla se ci sono bombe che devono esplodere

bool is_empty (Map mappa, int coordinata_x, int coordinata_y, char direction); //controlla se una casella della mappa é vuota o meno
bool particular_position (int coord_x, int coord_y); //controlla se il player si trova in una posizione speciale