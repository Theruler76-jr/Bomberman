#include "game.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

/* NOTA
 * per il commento del funzionamento di tutte le varie funzioni guardare nel header file, in questo file sono presenti
 * solo commenti che servono durante lo sviluppo/per ricordarmi aggiustamenti da fare in seguito.
*/

#include "game_over.h"



struct bomb_list {
    Bomb bomba;
    bomb_list *next;
};

struct Level {
    Map map;
    int time = 60 * 5;
    int level_number;
    int enemy;
    int time_left;
    bomb_list *bomb_queue;

    Level *previous = nullptr;
    Level *next = nullptr;
};

Level* find_last (Level* current) {
    if (current -> next == nullptr)
        return current;
    else
        return find_last (current -> next);
}

bomb_list* initialize_queue () {
    return nullptr;
}

Level* push_level (Level* head_level, int level_number) {
    Level *to_add = new Level;
    to_add -> map = Map();
    to_add -> map.livello(level_number);
    to_add ->level_number = level_number;
    to_add -> enemy = level_number * 3;
    to_add -> time_left = time_per_level;
    to_add -> bomb_queue = initialize_queue();
    to_add -> next = nullptr;
    if (head_level == nullptr) {
        head_level = to_add;
        to_add -> previous = nullptr;
        return head_level;
    } else {
        Level *last_in_list = find_last (head_level);
        to_add -> previous = last_in_list;
        last_in_list -> next = to_add;
        return head_level;
    }
}

Level* levels_initializer (Level *head_level) {
    for (int i = 0; i < numero_livelli; i++) {
        head_level = push_level(head_level, i + 1); //aggiungere tutti i parametri attuali
    }
    return head_level;
}



Level* remove_level (Level* current_level) {
    if (current_level -> next == nullptr && current_level -> previous == nullptr) //Significa che era l'ultimo livello quindi la partita é terminata
        return nullptr;
    Level *to_delete = current_level;
    to_delete -> next -> previous = to_delete -> previous;
    to_delete -> previous -> next = to_delete -> next;
    if (current_level -> next == nullptr) //In questo modo se é stato completato l'ultimo livello ma ne restano altri incompleti viene riportato al livello incompleto piú vicino
        current_level = current_level -> previous;       //se invece si volesse far ripartire dal primo basta fare una funzione ricorsiva ausiliaria
    else
        current_level = current_level -> next;
    delete to_delete;
    return current_level;
}

void write_score (int score) {
    move(2,100);
    printw("Score: %d", score);
}

void write_lives (Player giocatore) {
    move(4, 100);
    printw("Lives left: %d", giocatore.get_numero_vite());
}

void write_level (int number) {
    move(2, 50);
    printw("Level: %d", number);
}

Level* next_level (Level *current_level) {
    if (current_level -> next != nullptr)
        return current_level -> next;
    else
        return current_level;
}

Level* previous_level (Level *current_level) {
    if (current_level -> previous != nullptr)
        return current_level -> previous;
    else
        return current_level;
}

void write_enemy (Level *level) {
    move(2,10);
    if (level->enemy >= 10)
        printw("Enemy left: %d",level -> enemy);
    else
        printw("Enemy left: 0%d",level -> enemy);
}

void write_location (Player Giocatore, int score) {
    move (8,100);
    int x = Giocatore.get_coordinata_x(), y = Giocatore.get_coordinata_y();
    printw("Player in (%d,%d)",x, y);
}


void write_time_left (Level *current_level) {
    move (6,100);
    int seconds_left = current_level -> time_left;
    if (seconds_left >= 100)
        printw("Time left %d", seconds_left);
    else if (seconds_left >= 10)
        printw("Time left 0%d", seconds_left);
    else if (seconds_left >= 1)
        printw("Time left 00%d", seconds_left);
}

bool is_empty (Map mappa, int coordinata_x, int coordinata_y, char direction) {
    if (direction == 'w')
        coordinata_y--;
    if (direction == 's')
        coordinata_y++;
    if (direction == 'd')
        coordinata_x++;
    if (direction == 'a')
        coordinata_x--;

    if (mappa.pos(coordinata_x, coordinata_y) == 'v')
        return true;
    return false;
}

Level* move_player (char direction, Level* current_level, Player &Giocatore) {
    if (direction == 'd' && Giocatore.get_coordinata_x() == 40 && Giocatore.get_coordinata_y() == 10) {
        if (current_level -> enemy == 0)
            current_level = remove_level(current_level);
        else
            current_level = current_level -> next;

        Giocatore.move_x(-39);
        Giocatore.move_y(-9);
        current_level -> map.cambia(Giocatore.get_coordinata_x(),Giocatore.get_coordinata_y(),player_skin);
    } else if (is_empty(current_level -> map, Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), direction)) {
        if (current_level -> map.pos(Giocatore.get_coordinata_x(),Giocatore.get_coordinata_y()) != bomb_skin) //cosí nel caso ci sia una bomba lascia stampata quella
            current_level -> map.cambia(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), 'v'); //così sistemo la casella su cui era il giocatore

        if (direction == 'w')
            Giocatore.move_y(-1);
        if (direction == 's')
            Giocatore.move_y(+1);
        if (direction == 'd')
            Giocatore.move_x(1);
        if (direction == 'a')
            Giocatore.move_x(-1);
        current_level -> map.cambia(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), player_skin);
        move (10,100);
        printw("Detected movement %c", direction);
    } else {
        move (10,100);
        printw("Impossible movement");
    }
    return current_level;
}

void print_routine (Level* current_level, Player Giocatore, int score, WINDOW *win) {
    write_enemy(current_level);
    write_score(score);
    write_lives(Giocatore);
    write_level(current_level -> level_number);
    current_level -> map.stamp(win,38,3);
    write_location(Giocatore, score);
    write_time_left(current_level);
    wrefresh(win);
}


bomb_list* get_last (bomb_list *element) {
    if (element -> next == nullptr)
        return (element);
    else
        return (get_last(element -> next));
}


bomb_list* add_bomb (bomb_list *head, int coord_x, int coord_y, unsigned int time_placing, int molt_explosion, Map &map) {
        map.cambia(coord_x,coord_y,bomb_skin);
        bomb_list *to_add = new bomb_list;
        to_add -> bomba = Bomb (coord_x,coord_y,time_placing,molt_explosion);
        to_add -> next = nullptr;
        if (head == nullptr)
            head = to_add;
        else {
            bomb_list *last = get_last (head);
            last -> next = to_add;
        }
    return head;
}

bomb_list* check_bomb_status (bomb_list *head, unsigned int time, Player &Giocatore, Map &map) {
    if (head != nullptr && (time - head -> bomba.get_activation_time() >= 3)) {
        head -> bomba.esplodi(map, Giocatore);
        bomb_list* tmp = head;
        head = head -> next;
        delete tmp; //garbage eliminato
    }
    return head;
}

void update_status (bomb_list *&head, unsigned int time_occurred, Player &Giocatore, Map &map) {
    head = check_bomb_status(head, time_occurred, Giocatore, map);
}


char game_loop(WINDOW *win) {
    Player Giocatore = Player ();
    nodelay(stdscr, TRUE);
    bool  end_game = false;
    char input;
    int score = 0;
    unsigned long int frame = 0, seconds_occurred = 0;
    Level *current_level = nullptr;
    current_level = levels_initializer(current_level); //cosí ho creato tutti i livelli;
    current_level->map.cambia(Giocatore.get_coordinata_x(),Giocatore.get_coordinata_y(),player_skin);
    werase (win); //cancello il menu'
    box(win,0,0);
    wrefresh(win);
    //in fase di testing per saperlo, alla fine andra' rimosso e sistemato
    move (21,97);
    printw("Press E to drop a bomb");
    move (23,100);
    printw("Press Q to exit");
    while (!end_game) {
        if (seconds_occurred != clock()/CLOCKS_PER_SEC) { //serve per tenere traccia del tempo
            seconds_occurred++;
            current_level -> time_left--;
        }

        print_routine(current_level, Giocatore, score, win);
        input = getch();

        if (input == 'q')
            end_game = true;
        else if (input == 'p')
            current_level = next_level(current_level);
        else if (input == 'o')
            current_level = previous_level(current_level);
        else if (input == 'w' || input == 'a' || input == 's' || input == 'd')
            current_level = move_player(input,current_level,Giocatore);
        else if (input == 'z')
            end_game = !Giocatore.cambia_numero_vite(-1);
        else if (input == 'e')
            current_level -> bomb_queue = add_bomb(current_level -> bomb_queue, Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), seconds_occurred,1, current_level -> map);

        update_status(current_level -> bomb_queue, seconds_occurred,Giocatore, current_level -> map);
        //ATTENZIONE QUSTA PARTE DEVE RIMANERE SEMPRE PER ULTIMA, NEL CASO SI VOLESSE MODIFICARE SI DEVE SEMPRE E SOLO MODIFICARE LA COSTANTE PER CUI SI MOLTIPLICANO I
        //CLOCKS_PER_SEC SECONDO LA FORMULA k = 1/fps_desiderati
        while (frame == int (clock()/(CLOCKS_PER_SEC * 0.04))){} //in questo modo il gioco va a 25 fps
        frame++;
    }

    game_over_screen(win, Giocatore.get_numero_vite(), score);

    return 'H';

}