#include "game.h"
#include "Map.h"
#include "Player.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

/* NOTA
 * per il commento del funzionamento di tutte le varie funzioni guardare nell'header file, in questo file sono presenti
 * solo commenti che servono durante lo sviluppo/per ricordarmi aggiustamenti da fare in seguito.
*/


const int numero_livelli = 5; //questa dichiarazione é temporanea se si vuole rimuovere bisogna accordarsi su un numero

struct Level {
    Map map;
    int time = 60 * 5;
    int level_number;

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
    to_add -> map = Map();
    to_add -> map.livello(level_number);
    to_add ->level_number = level_number;
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
    if (current_level -> next == nullptr && current_level -> previous == nullptr) //Significa che era l'ultimo livello quindi l partita é terminata
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
    move(2, 10);
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

char game_loop(WINDOW *win) {
    Player Giocatore = Player ();
    initscr();
    nodelay(stdscr, FALSE); //serve per far andare getch() se no non funzia :/
    bool  end_game = false;
    char input;
    int score = 0;
    Level *current_level = nullptr;
    current_level = levels_initializer(current_level); //cosí ho creato tutti i livelli;
    werase (win); //cancello il menu'
    box(win,0,0);
    wrefresh(win);
    //in fase di testing per saperlo, alla fine andra' rimosso e sistemato
    move (23,100);
    printw("Press q to exit");
    while (!end_game) {
        write_score(score);
        write_lives(Giocatore);
        write_level(current_level -> level_number);
        current_level -> map.stamp(win,38,3);
        score++;
        wrefresh(win);
        input = getch();
        if (input == 'q')
            end_game = true;
        else if (input == 'd')
            current_level = next_level(current_level);
        else if (input == 'a')
            current_level = previous_level(current_level);
    }
    return 'Q';
}