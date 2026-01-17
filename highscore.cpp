#include "highscore.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <cstdlib>
#include <cstring>
#include <fstream>


void save_highscore(char name[], int score) {
    std::ofstream file;
    file.open("highscores.txt", std::ios_base::app);
    file << "\n" << name << "-" << score;
    file.close();
}


highscore* add_highscore(highscore* head, char name[], int score) {

    if (head == nullptr) {

        highscore* new_highscore = new highscore();

        strcpy(new_highscore->name, name);
        new_highscore->score = score;

        return new_highscore;

    }

    highscore* ptr = head;

    highscore* new_highscore = new highscore();

    strcpy(new_highscore->name, name);
    new_highscore->score = score;

    while (ptr->score >= score) {

        if (ptr->next == nullptr) {
            ptr->next = new_highscore;
            return head;
        }

        if (ptr->next->score < score) {
            highscore* tmp = ptr->next;
            ptr->next = new_highscore;
            new_highscore->next = tmp;
            return head;
        }

        ptr = ptr->next;

    }

    new_highscore->next = head;
    return new_highscore;

}


highscore* get_highscores() {

    std::ifstream file("highscores.txt");

    if (!file.is_open()) {
        return nullptr;
    }

    highscore* head = nullptr;

    char buffer[100];
    while (file.getline(buffer, 100)) {

        char* name = strtok(buffer, "-");
        char* score = strtok(nullptr, "");

        head = add_highscore(head, name, atoi(score));

    }

    file.close();
    return head;

}


int get_total_highscores(highscore* head) {
    if (head == nullptr) return 0;
    return 1 + get_total_highscores(head->next);
}


void free_memory(highscore* head) {
    if (head == nullptr) return;
    free_memory(head->next);
    delete head;
}



char highscore_loop(WINDOW *win) {

    werase(win);

    const char *title[5] = {
          "     _  _ _      _      ___                    ",
          "    | || (_)__ _| |_   / __| __ ___ _ _ ___ ___",
        R"(    | __ | / _` | ' \  \__ \/ _/ _ \ '_/ -_|_-<)",
        R"(    |_||_|_\__, |_||_| |___/\__\___/_| \___/__/)",
          "           |___/                               "
    };

    highscore* head = get_highscores();
    int total_highscores = get_total_highscores(head);
    highscore* ptr = head;

    keypad(win, TRUE);

    int width, height;
    getmaxyx(win, height, width);
    if (width == 1 || height == 1) {
        width = 120;
        height = 30;
    }

    int scoreboard_width = width / 2;
    int scoreboard_height = height / 3 * 2 - 1;

    WINDOW* scoreboard = newwin(scoreboard_height, scoreboard_width, 8, width / 4);
    box(scoreboard, 0, 0);


    int input;
    const char *menu[2] = {"Menu", "Quit"};
    int selection = 0;
    int scroll = 0;

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    while (true) {

        input = getch();

        if (input == KEY_LEFT || input == 'a' || input == 'A') {
            selection = 0;
        }

        if (input == KEY_RIGHT || input == 'd' || input == 'D') {
            selection = 1;
        }

        if (input == KEY_UP || input == 'w' || input == 'W') {
            if (scroll < 0) scroll += 2;
        }

        if (input == KEY_DOWN || input == 's' || input == 'S') {
            if (scroll > -total_highscores * 2 + scoreboard_height - 2) scroll -= 2;
        }

        if (input == 10 || input == ' ' || input == 'e' || input == 'E') {

            free_memory(head);
            nodelay(stdscr, TRUE);

            switch (selection) {
                case 0:
                    return 'M';
                case 1:
                    return 'Q';
                default:
                    return 'E';
            }

        }


        box(win, '|', '#');

        for (int i = 0; i < 5; i++) {   // prints ASCII title

            mvwprintw(win, 2 + i, 12, "%s", title[i]);

        }


        for (int i = 0; i < 2; i++) {   // prints menu options

            int y_pos = 4;
            int x_pos = (width / 6) * (4 + i) - strlen(menu[i]) / 2;

            mvwprintw(win, y_pos, x_pos - 2, " ");

            if (selection == i) {
            mvwprintw(win, y_pos, x_pos - 2, ">");
                wattron(win, COLOR_PAIR(1));
                wattron(win, A_BOLD);
            }

            mvwprintw(win, y_pos, x_pos, "%s", menu[i]);

            wattroff(win, COLOR_PAIR(1));
            wattroff(win, A_BOLD);

        }

        ptr = head;

        mvwaddch(win, height / 2, 26, ACS_UARROW);
        mvwaddch(win, height / 2 + 4, 26, ACS_DARROW);

        werase(scoreboard);
        box(scoreboard, 0, 0);

        for (int i = 1; ptr != nullptr && i <= total_highscores; i++) {    // prints leaderboard

            int y_pos = 2 * i + scroll;
            int x_pos = scoreboard_width / 2 - 16;

            if (y_pos <= 0 || y_pos >= scoreboard_height - 1) {
                ptr = ptr->next;
                continue;
            }

            if (i >= 10) x_pos--;

            if (i == 11 || i == 12 || i == 13) mvwprintw(scoreboard, y_pos, x_pos, "%dTH", i);
            else {
                switch (i % 10) {
                case 1:
                    mvwprintw(scoreboard, y_pos, x_pos, "%dST", i);
                    break;
                case 2:
                    mvwprintw(scoreboard, y_pos, x_pos, "%dND", i);
                    break;
                case 3:
                    mvwprintw(scoreboard, y_pos, x_pos, "%dRD", i);
                    break;
                default:
                    mvwprintw(scoreboard, y_pos, x_pos, "%dTH", i);
                }
            }

            if (i >= 10) x_pos++;

            mvwprintw(scoreboard, y_pos, x_pos + 6, "%s", ptr->name);
            mvwprintw(scoreboard, y_pos, scoreboard_width / 2 + 12, "%d", ptr->score);

            ptr = ptr->next;

        }

        wrefresh(win);
        wrefresh(scoreboard);

        nodelay(stdscr, FALSE);

    }
}