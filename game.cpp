#include "game.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

const int numero_livelli = 5; //questa dichiarazione é temporanea se si vuole rimuovere bisogna accordarsi su un numero

struct Level {
    Map map();

    int time = 60 * 5;

    Level *previous = nullptr;
    Level *next = nullptr;
};

//Funzione ausiliaria di push_level
Level* find_last (Level* current) {
    if (current -> next == nullptr)
        return current;
    else
        return find_last (current -> next);
}
//Funzione ausiliaria di Levels_initializer
Level* push_level (Level* head_level) {  //aggiungi i parametri che servono al livello per essere creato
    Level *to_add = new Level;
    //aggiungi tutte le inizializzazioni degli altri campi
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

//Con questa funzione creo la lista bidirezionale di tutti i livelli
Level* levels_initializer (Level *head_level) {
    for (int i = 0; i < numero_livelli; i++) {
        head_level = push_level(head_level); //aggiungere tutti i parametri attuali
    }
    return head_level;
}



//con questa funzione si elimina il livello passato per parametro e ritorna il livello successivo
Level* remove_level (Level* current_level) {
    if (current_level -> next == nullptr && current_level -> previous == nullptr) //Significa che era l'ultimo livello quindi l partita é terminata
        return nullptr;
    Level *to_delete = current_level;
    to_delete -> next -> previous = to_delete -> previous;
    to_delete -> previous -> next = to_delete -> next;
    if (current_level -> next == nullptr) //In questo modo se é stato completato l'ultimo livello ma ne restano altri incompleti viene riportato al livello incompleto piú vicino
        current_level = current_level -> previous;                                      //se invece si volesse far ripartire dal primo basta fare una funzione ricorsiva ausiliaria
    else
        current_level = current_level -> next;
    delete to_delete;
    return current_level;
}




char game_loop(WINDOW *win) {

    char input;
    Level *current_level = nullptr;
    current_level = levels_initializer(current_level);



    int score = 0;

    while (true) {

        input = getch();

        switch (input) {
            case 'q':
                return 'Q';
        }

        // Logica





        // disegno

        box(win, 0, 0);



        wrefresh(win);
        refresh();
        _sleep(100);
    }

}


