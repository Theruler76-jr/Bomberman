#pragma once

#include "Player.h"
#include "enemy.h"
#include "utility.h"
#include "Map.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <ctime>


const int numero_livelli = 5; //questa dichiarazione é temporanea se si vuole rimuovere bisogna accordarsi su un numero
const char player_skin = '@'; //così se vogliamo cambiare la skin lo si può fare nel chill
const int time_per_level = 200;
const int score_per_enemy = 10;
//lista di nemici
struct enemy_list {
    enemy *nemico;
    enemy_list *next;
};

//lista di item

class Item; //sennò non compila

struct item_list {
    Item *utility;
    item_list *next;
};
char game_loop(WINDOW *win);
struct  bomb_list;
struct Level {
    Map map = Map();
    int time = 60 * 5;
    int level_number;
    int enemy;
    int time_left = time_per_level;
    bomb_list *bomb_queue = nullptr;
    item_list *il = nullptr;
    enemy_list *el = nullptr;

    Level *previous = nullptr;
    Level *next = nullptr;
};
struct bomb_animation;

void write_score (int score, WINDOW* win); //scrive il punteggio attuale del giocatore
void write_lives (Player giocatore, WINDOW *win); //scrive il numero di vite rimanenti al giocatore
void write_level (int number,WINDOW *win); //scrive il numero di livello in cui si trova il giocatore
void write_time_left (Level *current_level,WINDOW *win); //scrive il numero di secondi rimasti per ogni livello
void print_routine (Level* current_level, Player Giocatore, int score, WINDOW *win); //stampa tutte le informazioni a schermo a ogni ciclo
void update_status (bomb_list *&head, unsigned int time_occurred, Player &Giocatore, Map &map, Level *&current_level, int &score, bomb_animation*& queue_bomb_animation); //aggiorna lo stato della mappa

Level* find_last (Level* current); //Funzione ausiliaria di push_level
Level* push_level (Level* head_level, int level_number, Player *pl); //Funzione ausiliaria di Levels_initializer
Level* levels_initializer (Level *head_level, Player *pl); //Con questa funzione creo la lista bidirezionale di tutti i livelli
Level* remove_level (Level* current_level); //con questa funzione si elimina il livello passato per parametro e ritorna il livello successivo
Level* next_level (Level *current_level); //porta il giocatore al livello successivo, non succede niente se é l'ultimo livello
Level* previous_level (Level *current_level); //porta il giocatore al livello precedente, non succede niente se é il primo livello
Level* move_player (char direction, Level* current_level, Player &Giocatore, int &score);//muove il player controllando di non star andando nei muri
Level* clean_heap (Level *current_level); //questa funzione cancella tutti gli eventuali livelli rimasi nella lista

bomb_list* add_bomb (bomb_list *head, int coord_x, int coord_y, unsigned int time_placing, int molt_explosion, Map &map, Player &Giocatore); //aggiunge una bomba alla lista di bombe del livello
bomb_list* get_last (bomb_list *element); //funzione ausiliaria di add_bomb
bomb_list* check_bomb_status (bomb_list *head, unsigned int time, Player &Giocatore, Map &map, Level *&current_level, int &score, bomb_animation* &queue_bomb_animation); //controlla se ci sono bombe che devono esplodere
bomb_list* clean_queue (bomb_list* head);//garbage collection della lista delle bombe


bomb_animation* update_list (bomb_animation* head_list, Map &mappa, Player &Giocatore, Level *&current_level); //updater della lista di animazione delle bombe
void write_animation (bomb_animation *&head_list, Map &mappa, enemy_list *&lista_nemici); //funzione che scrive sulla mappa l'animazione della bomba
void erase_animation (int coord_x, int coord_y, int moltiplicatore, Map &mappa, Player Giocatore, Level *&current_level); //funzione che cancella l'animazione delle bombe dalla mappa
bomb_animation* clean_queue (bomb_animation* head); //garbage collection della code delle animazioni delle bombe
bomb_animation* push_animation (int c_x, int c_y, int molt, bomb_animation* head_list); //aggiunge un'animazione alla coda
bomb_animation* get_last_bomb_animation (bomb_animation *head); //ausiliaria di push_animation

bool is_empty (Map mappa, int coordinata_x, int coordinata_y, char direction); //controlla se una casella della mappa é vuota o meno
bool particular_positionmv (int coord_x, int coord_y, char direction); //controlla se il player si trova in una posizione speciale
bool bomb_presence (bomb_list *list, int coord_x, int coord_y); //funzione ausiliaria utile per evitare bug quando si cancella l'animazione delle bombe

struct enemy_list;
enemy_list* rimuovi_nemico(enemy_list *el, int x, int y);

char convert_input (char input); //funzione che sistema l'input unificandolo al resto del codice