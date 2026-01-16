#pragma once

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif


struct highscore{
    char name[16];
    int score = 0;
    highscore* next = nullptr;
};

void save_highscore(char name[], int score);
highscore* add_highscore(highscore* head, char name[], int score);
highscore* get_highscores();
void free_memory(highscore* head);

char highscore_loop(WINDOW *win);
