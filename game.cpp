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
    Map map = Map();
    int time = 60 * 5;
    int level_number;
    int enemy;
    int time_left = time_per_level;
    bomb_list *bomb_queue = nullptr;

    Level *previous = nullptr;
    Level *next = nullptr;
};

Level* find_last (Level* current) {
    if (current -> next == nullptr)
        return current;
    else
        return find_last (current -> next);
}

Level* push_level (Level* head_level, int level_number) {
    Level *to_add = new Level;
    to_add -> map.livello(level_number);
    to_add -> level_number = level_number;
    to_add -> enemy = level_number * 3;

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

void write_score (int score, WINDOW *win) {
    mvwprintw(win,2,100,"Score: %d", score);
}

void write_lives (Player Giocatore, WINDOW *win) {
     const char *lives_title [4] = {
          " _   _  _   _  ___  __   ",
         R"(| | | || \ / || __/' _/)",
         R"(| |_| |`\ V /'| _|`._`. )",
         R"(|___|_|  \_/  |___|___/ )",
    }; //Stforek

    const char *heart [4] = {
        " *  *             ",
        "******            ",
        " ****             ",
        "  **               "
    };

    //stampa della scritta LIVES
    for (int i = 0; i < 4; i++) {
        mvwprintw(win,6+i,50,lives_title[i]);
    }

    //stampa dei cuori
    for (int j = 0; j < Giocatore.get_numero_vite(); j++) {
        for (int z = 0; z < 4; z++) {
            mvwprintw(win,6 + z, 75 + (j * 8),heart[z]);
        }
    }

}

void write_level (int number, WINDOW *win) {
    //mvwprintw(win,2,50,"Level: %d", number);
    const char *level_title [4] = {
          " _   ___ _   _  ___ _",
        R"(| | | __| \ / || __| |   )",
        R"(| |_| _|`\ V /'| _|| |_  )",
        R"(|___|___| \_/  |___|___| )"
    };

    for (int i = 0; i < 4; i++) {
        mvwprintw(win,2 + i, 5,level_title[i]);
    }

    const char *numbers [20] = {
           " __    ",
           "/  |   ",
           "`7 |   ",
           " |_|   ",
           " ___   ",
           "(_  |  ",
           " / /   ",
           "|___|  ",
           " __    ",
           "|__`.  ",
           " |_ |  ",
           "|__.   ",
           " _  _  ",
           "| || | ",
           "`._  _|",
           "   |_| ",
           " ___   ",
           "| __|  ",
           "`._`.  ",
           "!__.'  ",
    };

    for (int i = 0; i < 4; i++) {
        mvwprintw(win,2 + i, 32,numbers[i + ((number -1) * 4)]);
    }
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

void write_enemy (Level *level, WINDOW *win) {
    if (level->enemy >= 10)
        mvwprintw(win,10,100,"Enemy left: %d",level -> enemy);
    else
        mvwprintw(win,10,100,"Enemy left: 0%d",level -> enemy);
}

void write_location (Player Giocatore, WINDOW *win) {
    mvwprintw(win,8,100,"Player in (%d,%d)",Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y());
}


void write_time_left (Level *current_level, WINDOW *win) {
    int seconds_left = current_level -> time_left;
    if (seconds_left >= 100)
        mvwprintw(win,6,100,"Time left %d", seconds_left);
    else if (seconds_left >= 10)
        mvwprintw(win,6,100,"Time left 0%d", seconds_left);
    else if (seconds_left >= 1)
        mvwprintw(win,6,100,"Time left 00%d", seconds_left);
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
    }
    return current_level;
}

void print_routine (Level* current_level, Player Giocatore, int score, WINDOW *win) {
    write_enemy(current_level,win);
    write_score(score,win);
    write_lives(Giocatore,win);
    write_level(current_level -> level_number,win);
    current_level -> map.stamp(win,5,7);
    write_location(Giocatore, win);
    write_time_left(current_level,win);
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



void print_number (WINDOW *win, int number, int digits, int coordinata_x, int coordinata_t) {

}













































char game_loop(WINDOW *win) {

    nodelay(stdscr, TRUE);

    werase(win); //cancello il menu'
    box(win, 0, 0);

    bool end_game = false;
    char input;
    int score = 0;
    unsigned long int frame = 0, seconds_occurred = clock()/CLOCKS_PER_SEC; //cosí se il game_loop parte dopo non ci sono problemi

    Player Giocatore = Player();

    Level *current_level = nullptr;
    current_level = levels_initializer(current_level); //cosí ho creato tutti i livelli;
    current_level->map.cambia(Giocatore.get_coordinata_x(),Giocatore.get_coordinata_y(),player_skin);

    //in fase di testing per saperlo, alla fine andra' rimosso e sistemato
    mvprintw(21, 97, "Press E to drop a bomb");
    mvprintw(23, 100, "Press Q to exit");

    while (!end_game) {
        if (seconds_occurred != clock()/CLOCKS_PER_SEC) { //serve per tenere traccia del tempo
            seconds_occurred++;
            current_level -> time_left--;
        }

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
        else if (input == ' ')
            current_level -> bomb_queue = add_bomb(current_level -> bomb_queue, Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), seconds_occurred,1, current_level -> map);
        //parte degli update
        update_status(current_level -> bomb_queue, seconds_occurred,Giocatore, current_level -> map);
        if (Giocatore.get_numero_vite() <= 0)
            end_game = true;

        print_routine(current_level, Giocatore, score, win);
        wrefresh(win);

        //ATTENZIONE QUSTA PARTE DEVE RIMANERE SEMPRE PER ULTIMA, NEL CASO SI VOLESSE MODIFICARE SI DEVE SEMPRE E SOLO MODIFICARE LA COSTANTE PER CUI SI MOLTIPLICANO I
        //CLOCKS_PER_SEC SECONDO LA FORMULA k = 1/fps_desiderati
        while (frame == int (clock()/(CLOCKS_PER_SEC * 0.04))){} //in questo modo il gioco va a 25 fps
        frame++;
    }

    game_over_screen(win, Giocatore.get_numero_vite(), score);

    return 'H';

}