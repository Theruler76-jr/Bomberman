#include "game.h"
#include "enemy.h"
#include "utility.h"
#include "game_over.h"


#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

/* NOTA
 * per il commento del funzionamento di tutte le varie funzioni guardare nel header file, in questo file sono presenti
 * solo commenti che servono durante lo sviluppo/per ricordarmi aggiustamenti da fare in seguito.
*/



const int inizio_mappa_x = 32;
const int inizio_mappa_y = 4;
const int player_speed = 3; // ogni quanti fps il player si puó muovere
const int frame_per_animation = 20;
const char skin_bomb_animation = bomb_exp;

//lista di nemici
struct enemy_list;

//lista di item
struct item_list;

//ti metto le funzioni che creano la lista di nemici e item in base al livello

enemy_list* push_nemici(enemy_list* el, enemy *_nemico) {
    enemy_list *temp=new enemy_list;
    temp->nemico=_nemico;
    temp->next=el;
    return(temp);
}

enemy_list* crea_nemici(int livello, Map *_mappa) {
    enemy_list *en=nullptr;
    if (livello==1) {
        en=push_nemici(en, new base_enemy(_mappa));
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new base_enemy(_mappa));
    }
    else if (livello==2) {
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new base_enemy(_mappa));
    }
    else if (livello==3) {
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new advanced_enemy(_mappa));
    }
    else if (livello==4) {
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new advanced_enemy(_mappa));
        en=push_nemici(en,new advanced_enemy(_mappa));
    }
    else if (livello==5) {
        en=push_nemici(en,new base_enemy(_mappa));
        en=push_nemici(en,new advanced_enemy(_mappa));
        en=push_nemici(en,new advanced_enemy(_mappa));
        en=push_nemici(en,new advanced_enemy(_mappa));
    }
    return(en);
}

enemy_list* rimuovi_nemico(enemy_list *el, int x, int y) {
    enemy_list *temp=el, *prev=nullptr;
    while (temp!=nullptr) {
        if (temp->nemico->get_x()==x && temp->nemico->get_y()==y) {
            enemy_list *da_eliminare=temp;
            if (prev==nullptr) {
                el=el->next;
                temp=el;
            }
            else {
                prev->next=temp->next;
                temp=temp->next;
            }
            delete da_eliminare->nemico;
            delete da_eliminare;
        }
        else {
            prev=temp;
            temp=temp->next;
        }
    }
    return(el);
}

enemy_list* elimina_enemy_exp(enemy_list *el, int &score, Map *mappa, Level *lv) {
    enemy_list *temp=el, *prev=nullptr;
    while (temp!=nullptr) {
        int x_ax=el->nemico->get_x(), y_ax=el->nemico->get_y();
        if (mappa->pos(x_ax,y_ax)==bomb_exp) {
            temp->nemico->punteggio(score);
            (lv->enemy)--;

            enemy_list *da_eliminare=temp;
            if (prev==nullptr) {
                el=temp->next;
                temp=el;
            }
            else {
                prev->next=temp->next;
                temp=temp->next;
            }
            delete da_eliminare->nemico;
            delete da_eliminare;
        }
        else {
            prev=temp;
            temp=temp->next;
        }
    }
    return(el);
}

item_list* push_item(item_list* il, Item *_utility) {
    item_list *temp=new item_list;
    temp->utility=_utility;
    temp->next=il;
    return(temp);
}

item_list* crea_item(int livello, Map *_mappa, Player *pl) {
    item_list *il=nullptr;
    if (livello==1) {
        il=push_item(il,new raggio_bomba(_mappa, pl));
        il=push_item(il,new num_bombe(_mappa, pl));
        il=push_item(il,new nuova_vita(_mappa, pl));
        il=push_item(il,new add_punti(_mappa, pl));
    }
    else if (livello==2) {
        il=push_item(il,new nuova_vita(_mappa,pl));
        il=push_item(il,new num_bombe(_mappa, pl));
        il=push_item(il,new add_punti(_mappa, pl));
        il=push_item(il,new add_punti(_mappa, pl));

    }
    else if (livello==3) {
        il=push_item(il,new nuova_vita(_mappa,pl));
        il=push_item(il,new raggio_bomba(_mappa, pl));
        il=push_item(il,new add_punti(_mappa, pl));
        il=push_item(il,new nuova_vita(_mappa,pl));
    }
    else if (livello==4) {
        il=push_item(il,new raggio_bomba(_mappa, pl));
        il=push_item(il,new nuova_vita(_mappa,pl));
        il=push_item(il,new add_tempo(_mappa, pl));
        il=push_item(il,new add_tempo(_mappa, pl));
    }
    else if (livello==5) {
        il=push_item(il,new nuova_vita(_mappa,pl));
        il=push_item(il,new num_bombe(_mappa, pl));
        il=push_item(il,new add_tempo(_mappa, pl));
        il=push_item(il,new add_tempo(_mappa, pl));
    }
    return(il);
}

void move_enemies(enemy_list* el, Player *pl) {
    enemy_list* temp=el;
    while (temp!=nullptr) {
        temp->nemico->move(pl);
        temp=temp->next;
    }
}

item_list* controlla_item(Level *lv, Player *pl, item_list *il, int &score){
    item_list *temp=il, *prev=nullptr;
    while (temp!=nullptr) {
        if (temp->utility->get_x()==pl->get_coordinata_x() && temp->utility->get_y()==pl->get_coordinata_y()) {
            temp->utility->applica_effetto(lv,score);
            if (prev==nullptr) {
                il=il->next;
                delete temp->utility;
                delete temp;
                return(il);
            }
            else {
                prev->next=temp->next;
                delete temp->utility;
                delete temp;
                return(il);
            }
        }
        prev=temp;
        temp=temp->next;
    }
    return(il);
}

char controlla_pos(item_list *il, int x, int y) {
    item_list *temp=il;
    while (temp!=nullptr) {
        if (temp->utility->get_x()==x && temp->utility->get_y()==y) {
            return(temp->utility->get_aspetto());
        }
        temp=temp->next;
    }
    return('v');
}

struct bomb_list {
    Bomb bomba;
    bomb_list *next;
};

struct Level;

Level* find_last (Level* current) {
    if (current -> next == nullptr)
        return current;
    else
        return find_last (current -> next);
}

Level* push_level (Level* head_level, int level_number, Player *pl) {
    Level *to_add = new Level;
    to_add -> map.livello(level_number);
    to_add -> level_number = level_number;
    if (level_number<3) {
        to_add -> enemy = 3;
    }
    else {
        to_add -> enemy = 4;
    }
    to_add -> el = crea_nemici(level_number,&(to_add->map));
    to_add ->il = crea_item(level_number,&(to_add->map),pl);

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

Level* levels_initializer (Level *head_level, Player *pl) {
    for (int i = 0; i < numero_livelli; i++) {
        head_level = push_level(head_level, i + 1,pl); //aggiungere tutti i parametri attuali
    }
    return head_level;
}



Level* remove_level (Level* current_level) {
    if (current_level -> next == nullptr && current_level -> previous == nullptr) //Significa che era l'ultimo livello quindi la partita é terminata
        return nullptr;
    Level *to_delete = current_level;
    to_delete -> next -> previous = to_delete -> previous;
    if (to_delete -> previous != nullptr)
        to_delete -> previous -> next = to_delete -> next;
    if (current_level -> next == nullptr) //In questo modo se é stato completato l'ultimo livello ma ne restano altri incompleti viene riportato al livello incompleto piú vicino
        current_level = current_level -> previous;       //se invece si volesse far ripartire dal primo basta fare una funzione ricorsiva ausiliaria
    else
        current_level = current_level -> next;
    delete to_delete;
    return current_level;
}

void write_score (int score, WINDOW *win) {
    const char *score_title[4] = {
     "  __   ___ __  ___ ___  ",
     R"(/'__/ / _//__\| _ \ __| )",
     R"(`._`.| \_| \/ | v / _|  )",
     R"(|___/ \__/\__/|_|_\___| )"
    };

    for (int i = 0; i < 4; i++) {
        mvwprintw(win, inizio_mappa_y + 7 + i, inizio_mappa_x + 48, "%s", score_title[i]);
    }

    //con questo if centro le cifre dei numeri
    int x = 0;
    if (score < 100)
        x = 58;
    else
        x = 57;

    mvwprintw(win, inizio_mappa_y + 12, inizio_mappa_x + x, "%d",score);
}

void write_lives (Player Giocatore, WINDOW *win) {
     const char *lives_title [4] = {
          " _   _  _   _  ___  __   ",
         R"(| | | || \ / || __/'__/)",
         R"(| |_| |`\ V /'| _|`._`. )",
         R"(|___|_|  \_/  |___|___/ )",
    }; //Stforek

    //stampa della scritta LIVES
    for (int i = 0; i < 4; i++) {
        mvwprintw(win,inizio_mappa_y+ i, inizio_mappa_x + 48,"%s",lives_title[i]);
    }

    //stampa dei cuori
    mvwprintw(win,inizio_mappa_y + 5, inizio_mappa_x + 55, "             "); //unico modo per gestire bene i cuori
    for (int j = 0; j < Giocatore.get_numero_vite(); j++) {
        mvwaddch(win, inizio_mappa_y + 5, inizio_mappa_x + 55 + (j * 3), ACS_DIAMOND);
    }

}

void write_level (int number, WINDOW *win) {
    //mvwprintw(win,2,50,"Level: %d", number);
    const char *level_title [16] = {
        "   __   ",
        "  / /   ",
        " / /__  ",
        "/____/_ ",
        "  / __/ ",
        " / _/   ",
        "/___/ __",
        " | | / /",
        " | |/ / ",
        " |___/_ ",
        "  / __/ ",
        " / _/   ",
        "/___/   ",
        "  / /   ",
        " / /__  ",
        "/____/  "
    };

    for (int i = 0; i < 16; i++) {
        mvwprintw(win,inizio_mappa_y + i, inizio_mappa_x - 12, "%s", level_title[i]);
    }

    const char *numbers [20] = {
       "  ___     ",
       " <  /     ",
       " / /      ",
       "/_/       ",
       "  ___     ",
       " |_  |    ",
       " / __/    ",
       "/____/    ",
       "  ____    ",
       " |_  /    ",
       " _/_ <    ",
       "/____/    ",
       "  ____    ",
       " / / /    ",
       "/_  _/    ",
       "/_/       ",
       "   ____   ",
       "  / __/   ",
       R"( /__ \ )",
       "/____/    "

    };

    for (int i = 0; i < 4; i++) {
        mvwprintw(win,inizio_mappa_y + 16 + i, inizio_mappa_x - 12, "%s", numbers[i + ((number -1) * 4)]);
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


void write_time_left (Level *current_level, WINDOW *win) {

    const char *time_title[4] = {
        " _____ _ __ __ ___  ",
        "|_   _| |  V  | __| ",
        R"(  | | | | \_/ | _|  )",
        "  |_| |_|_| |_|___| "
    };

    for (int i = 0; i < 4; i++) {
        mvwprintw(win,inizio_mappa_y + 14 + i, inizio_mappa_x + 49, "%s", time_title[i]);
    }
        mvwprintw(win,inizio_mappa_y + 19, inizio_mappa_x + 57,"%d  ", current_level -> time_left);
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

    if (mappa.pos(coordinata_x, coordinata_y) != 'I'      //condizioni per far muovere il plyer
        && mappa.pos(coordinata_x, coordinata_y) != 'm'
        && mappa.pos(coordinata_x, coordinata_y) != bomb_skin
        && mappa.pos(coordinata_x, coordinata_y) != 'R'
        && mappa.pos(coordinata_x, coordinata_y) != 'L'
        && mappa.pos(coordinata_x, coordinata_y) != 'N'
        && mappa.pos(coordinata_x, coordinata_y) != 'P'
        && mappa.pos(coordinata_x, coordinata_y) != 'T')
        return true;

    return false;
}

bool particular_positionmv (int coord_x, int coord_y, char direction) {
    if (coord_y == 10) {
        if (coord_x == 0 && direction == 'a')
            return true;
        if (coord_x == 40 && direction == 'd')
            return true;
        return false;
    }

    return false;
}


Level* move_player (char direction, Level* current_level, Player &Giocatore, int &score) {

    bool modified = false;

    //calcolo la nuova posizione del giocatore
    if (particular_positionmv(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), direction)) { //caso in cui potrebbe dover cambiare mappa

        //cancello il giocatore dalla posizione attuale in cui é
        if (current_level -> map.pos(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y()) != bomb_skin)
            current_level -> map.cambia(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), 'v');

        // controllo se deve essere eliminata la mappa
        if (direction == 'd' && Giocatore.get_coordinata_x() == 40 && current_level -> next != nullptr) {
            if (current_level -> enemy == 0) {
                score += current_level -> time_left;
                current_level = remove_level(current_level);
            }
            else
                current_level = next_level(current_level);

            Giocatore.move_x(-40);
        }
        else if (direction == 'a' && Giocatore.get_coordinata_x() == 0 && current_level -> previous != nullptr) {
            current_level = previous_level(current_level);
            Giocatore.move_x(40);
        }

        modified = true;

    } else {
        if (is_empty (current_level -> map, Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), direction)) {

            //cancello il giocatore dalla posizione attuale in cui é
            if (current_level -> map.pos(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y()) != bomb_skin)
                current_level -> map.cambia(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), 'v');

            //muovo il giocatore
            if (direction == 'w')
                Giocatore.move_y(-1);
            if (direction == 's')
                Giocatore.move_y(1);
            if (direction == 'd')
                Giocatore.move_x(1);
            if (direction == 'a')
                Giocatore.move_x(-1);

            if (current_level -> map.pos(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y()) == skin_bomb_animation) {
                Giocatore.cambia_numero_vite(-1);
                Giocatore.immunity();
            } else
                Giocatore.vulnerable();

            modified = true;
        }
    }

    //riscrivo il giocatore nella posizione "aggiornata"
    if (modified)
        current_level -> map.cambia(Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), player_skin);
    return current_level;
}

void print_routine (Level* current_level, Player Giocatore, int score, WINDOW *win) {
    write_score(score,win);
    write_lives(Giocatore,win);
    write_level(current_level -> level_number,win);
    current_level -> map.stamp(win,inizio_mappa_x,inizio_mappa_y);
    write_time_left(current_level,win);
    wrefresh(win);
}

struct bomb_animation {
    int coord_x;
    int coord_y;
    int moltiplicatore;
    int ticks = 20;
    bomb_animation* next = nullptr;
};

bomb_animation* get_last_bomb_animation (bomb_animation *head) {
    if (head -> next == nullptr)
        return head;
    else
        return get_last_bomb_animation (head);
}

bomb_animation* push_animation (int c_x, int c_y, int molt, bomb_animation* head_list) {
    bomb_animation *to_add = new bomb_animation;
    to_add -> coord_x = c_x;
    to_add -> coord_y = c_y;
    to_add -> moltiplicatore = molt;

    if (head_list == nullptr) {
        head_list = to_add;
        return head_list;
    }

    bomb_animation *last = get_last_bomb_animation (head_list);
    last -> next = to_add;
    return head_list;
}

void write_animation (bomb_animation *&head_list, Map &mappa, enemy_list *&lista_nemici) {
    if (head_list != nullptr) {
        int enemy_killed = 0, coord_x_destra = head_list -> coord_x, coord_x_sinistra = head_list -> coord_x, coord_y_sopra = head_list -> coord_y, coord_y_sotto = head_list -> coord_y;
        bool muro_dx = false, muro_sx = false, muro_up = false, muro_dw = false;
        for (int shift = 0; shift <= head_list -> moltiplicatore; shift++) {

            if (!muro_up) {
                if (mappa.pos(head_list -> coord_x, coord_y_sopra) == 'I')
                    muro_up = true;
                else
                    mappa.cambia (head_list -> coord_x, coord_y_sopra, skin_bomb_animation);
            }

            if (!muro_dw) {
                if (mappa.pos(head_list -> coord_x, coord_y_sotto) == 'I')
                    muro_dw = true;
                else
                    mappa.cambia (head_list -> coord_x, coord_y_sotto, skin_bomb_animation);
            }

            if (!muro_dx) {
                if (mappa.pos(coord_x_destra, head_list -> coord_y) == 'I')
                    muro_dx = true;
                else
                    mappa.cambia (coord_x_destra, head_list -> coord_y, skin_bomb_animation);
            }

            if (!muro_sx) {
                if (mappa.pos(coord_x_sinistra, head_list -> coord_y) == 'I')
                    muro_sx = true;
                else
                    mappa.cambia (coord_x_sinistra, head_list -> coord_y, skin_bomb_animation);
            }

            //aggiorno le coordinate
            coord_x_destra ++;
            coord_x_sinistra --;
            coord_y_sopra ++;
            coord_y_sotto --;
        }

        write_animation(head_list -> next, mappa, lista_nemici);
    }

}

void erase_animation (int coord_x, int coord_y, int moltiplicatore, Map &mappa, Player Giocatore, Level* current_level) {
    int coord_x_destra = coord_x, coord_x_sinistra = coord_x, coord_y_sopra = coord_y, coord_y_sotto = coord_y;
    bool muro_dx = false, muro_sx = false, muro_up = false, muro_dw = false;
    for (int shift = 0; shift <= moltiplicatore; shift++) {

        if (!muro_up) {
            if (mappa.pos(coord_x, coord_y_sopra) == 'I')
                muro_up = true;
            else if (Giocatore.get_coordinata_x() == coord_x && Giocatore.get_coordinata_y() == coord_y_sopra)
                mappa.cambia(coord_x, coord_y_sopra, player_skin);
            else
                mappa.cambia (coord_x, coord_y_sopra, controlla_pos(current_level -> il, coord_x, coord_y_sopra));
        }

        if (!muro_dw) {
            if (mappa.pos(coord_x, coord_y_sotto) == 'I')
                muro_dw = true;
            else if (Giocatore.get_coordinata_x() == coord_x && Giocatore.get_coordinata_y() == coord_y_sotto)
                mappa.cambia(coord_x, coord_y_sotto, player_skin);
            else
                mappa.cambia (coord_x, coord_y_sotto, controlla_pos(current_level -> il, coord_x, coord_y_sopra));
        }

        if (!muro_dx) {
            if (mappa.pos(coord_x_destra, coord_y) == 'I')
                muro_dx = true;
            else if (Giocatore.get_coordinata_x() == coord_x_destra && Giocatore.get_coordinata_y() == coord_y)
                mappa.cambia(coord_x_destra, coord_y, player_skin);
            else
                mappa.cambia (coord_x_destra, coord_y, controlla_pos(current_level -> il, coord_x_destra, coord_y));
        }

        if (!muro_sx) {
            if (mappa.pos(coord_x_sinistra, coord_y) == 'I')
                muro_sx = true;
            else if (Giocatore.get_coordinata_x() == coord_x_sinistra && Giocatore.get_coordinata_y() == coord_y)
                mappa.cambia(coord_x_sinistra, coord_y, player_skin);
            else
                mappa.cambia (coord_x_sinistra, coord_y, controlla_pos(current_level -> il, coord_x_sinistra, coord_y));
        }

        //aggiorno le coordinate
        coord_x_destra ++;
        coord_x_sinistra --;
        coord_y_sopra ++;
        coord_y_sotto --;
    }
}


bomb_animation* update_list (bomb_animation* head_list, Map &mappa, Player &Giocatore, Level *&current_level) {
    if (head_list != nullptr) {
        head_list -> ticks --;
        if (head_list -> ticks == 0) {
            bomb_animation *to_delete = head_list;
            erase_animation(head_list ->coord_x, head_list -> coord_y, head_list -> moltiplicatore, mappa, Giocatore, current_level);
            head_list = head_list ->next;
            delete to_delete;
            return update_list (head_list, mappa, Giocatore, current_level);
        } else {
            head_list -> next = update_list(head_list -> next, mappa, Giocatore, current_level);
            return head_list;
        }
    }
    return nullptr;
}


bomb_list* get_last (bomb_list *element) {
    if (element -> next == nullptr)
        return (element);
    else
        return (get_last(element -> next));
}


bomb_list* add_bomb (bomb_list *head, int coord_x, int coord_y, unsigned int time_placing, int molt_explosion, Map &map, Player &Giocatore) {
    if (Giocatore.get_bombe_schierate() < Giocatore.get_numero_bombe()) {
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
        Giocatore.cambia_numero_bombe_schierate(1);
    }
    return head;
}

bomb_list* check_bomb_status (bomb_list *head, unsigned int time, Player &Giocatore, Map &map, Level *&current_level, int &score, bomb_animation* &queue_bomb_animation) {
    if (head != nullptr && (time - head -> bomba.get_activation_time() >= 3)) {

        int bomb_x = head -> bomba.get_coordinata_x(), bomb_y = head -> bomba.get_coordinata_y();

        //faccio esplodere la bomba e controllo se ho ucciso un nemico
        int enemy_killed = head -> bomba.esplodi(map, Giocatore, score, current_level -> el);

        // gestisco l'animazione della bomba che esplode
        queue_bomb_animation = push_animation (bomb_x, bomb_y, Giocatore.get_moltiplicatore_bombe(), queue_bomb_animation);
        write_animation(queue_bomb_animation, map, current_level -> el);

        current_level -> enemy -= enemy_killed;

        bomb_list* tmp = head;
        head = head -> next;
        delete tmp; //garbage eliminato
    }
    return head;
}

void update_status (bomb_list *&head, unsigned int time_occurred, Player &Giocatore, Map &map, Level *&current_level, int &score, bomb_animation*& queue_bomb_animation) {
    head = check_bomb_status(head, time_occurred, Giocatore, map, current_level, score, queue_bomb_animation);
}


char game_loop(WINDOW *win) {

    nodelay(stdscr, TRUE);

    werase(win); //cancello il menu'
    box(win, 0, 0);

    bool end_game = false, time_exipired = false;
    char input;
    int score = 0, ticks_player = 0;
    unsigned long int frame = 0, seconds_occurred = clock()/CLOCKS_PER_SEC, clock_start = clock(); //cosí se il game_loop parte dopo non ci sono problemi

    Player Giocatore = Player();
    Player *plptr=&Giocatore;

    Level *current_level = nullptr;
    current_level = levels_initializer(current_level,plptr); //cosí ho creato tutti i livelli;
    current_level->map.cambia(Giocatore.get_coordinata_x(),Giocatore.get_coordinata_y(),player_skin);
    Map *mapptr=&current_level->map;

    bomb_animation *queue_bomb_animation = nullptr;

    while (!end_game) {
        if (seconds_occurred != clock()/CLOCKS_PER_SEC) { //serve per tenere traccia del tempo
            seconds_occurred++;
            if (current_level -> enemy > 0)
                current_level -> time_left--;
        }

        input = getch();

        if (input == 'q')
            end_game = true;
        else if (input == 'p')
            current_level = next_level(current_level);
        else if (input == 'o')
            current_level = previous_level(current_level);
        else if ((input == 'w' || input == 'a' || input == 's' || input == 'd') && ticks_player == 0) {
            current_level = move_player(input,current_level,Giocatore,score);
            ticks_player = player_speed;
        }
        else if (input == 'z')
            end_game = !Giocatore.cambia_numero_vite(-1);
        else if (input == ' ')
            current_level -> bomb_queue = add_bomb(current_level -> bomb_queue, Giocatore.get_coordinata_x(), Giocatore.get_coordinata_y(), seconds_occurred,Giocatore.get_moltiplicatore_bombe(), current_level -> map, Giocatore);
        else if (input == 'e')
            current_level -> enemy --;


        //parte degli update
        update_status(current_level -> bomb_queue, seconds_occurred,Giocatore, current_level -> map, current_level, score, queue_bomb_animation);
        if (current_level -> time_left == 0)
            time_exipired = true;
        if (Giocatore.get_numero_vite() <= 0 || time_exipired)
            end_game = true;
        if (ticks_player > 0)
            ticks_player--;

        queue_bomb_animation = update_list(queue_bomb_animation, current_level -> map, Giocatore, current_level);

        current_level->il=controlla_item(current_level,plptr,current_level->il,score);
        current_level->el=elimina_enemy_exp(current_level->el,score,mapptr,current_level);
        move_enemies(current_level->el,plptr);
        print_routine(current_level, Giocatore, score, win);

        //ATTENZIONE QUSTA PARTE DEVE RIMANERE SEMPRE PER ULTIMA, NEL CASO SI VOLESSE MODIFICARE SI DEVE SEMPRE E SOLO MODIFICARE LA COSTANTE PER CUI SI MOLTIPLICANO I
        //CLOCKS_PER_SEC SECONDO LA FORMULA k = 1/fps_desiderati
        while (frame == int ((clock() - clock_start)/(CLOCKS_PER_SEC * 0.04))){} //in questo modo il gioco va a 25 fps
        frame++;
    }

    //per crespi: la boolena che volevi è: time_expired
    game_over_screen(win, Giocatore.get_numero_vite(), score, time_exipired);

    return 'H';

}