#include "highscore.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <cstdlib>
#include <cstring>


void game_over_screen(WINDOW *win, int lives, int score) {

    const char *text_lose[4] = {
        "__   __          ___  _        _ _ ",
       R"(\ \ / /__ _  _  |   \(_)___ __| | |)",
       R"( \ V / _ \ || | | |) | / -_) _` |_|)",
       R"(  |_|\___/\_,_| |___/|_\___\__,_(_))"
    };

    const char *text_win[4] = {
          "__   __         __      __ _      _ ",
        R"(\ \ / /__ _  _  \ \    / /(_)_ _ | |)",
        R"( \ V / _ \ || |  \ \/\/ / | | ' \|_|)",
        R"(  |_|\___/\_,_|   \_/\_/  |_|_||_(_))"
    };

    int screen_width, screen_height;
    getmaxyx(win, screen_height, screen_width);
    if (screen_width == 1 || screen_height == 1) {
        screen_width = 120;
        screen_height = 30;
    }

    int dialog_width = 80;
    int dialog_height = 18;

    WINDOW *dialog = newwin(dialog_height, dialog_width, screen_height / 2 - dialog_height / 2, screen_width / 2 - dialog_width / 2);
    nodelay(dialog, TRUE);

    char input;

    while (true) {

        input = wgetch(dialog);

        if (input == 10) break;

        box(dialog, 0, 0);

        //wattron(dialog, A_BLINK);

        for (int i = 0; i < 4; i++) {   // prints game over message

            if (lives == 0) {
                mvwprintw(dialog, 2 + i, dialog_width/2 - strlen(text_lose[i]) / 2, "%s", text_lose[i]);
            } else {
                mvwprintw(dialog, 2 + i, dialog_width/2 - strlen(text_win[i]) / 2, "%s", text_win[i]);
            }

        }

        wattroff(dialog, A_BLINK);

        wattron(dialog, A_BOLD);
        mvwprintw(dialog, 7, dialog_width/2 - 6, "score: %d", score);
        wattroff(dialog, A_BOLD);


        wrefresh(dialog);

    }

}




char highscore_loop(WINDOW *win) {

    werase(win);

    const char *title[5] = {
          "     _  _ _      _      ___                    ",
          "    | || (_)__ _| |_   / __| __ ___ _ _ ___ ___",
        R"(    | __ | / _` | ' \  \__ \/ _/ _ \ '_/ -_|_-<)",
        R"(    |_||_|_\__, |_||_| |___/\__\___/_| \___/__/)",
          "            |___/                                "
    };

    keypad(win, TRUE);

    int width, height;
    getmaxyx(win, height, width);
    if (width == 1 || height == 1) {
        width = 120;
        height = 30;
    }

    int input;
    const char *menu[2] = {"Menu", "Quit"};
    int selection = 0;

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

        if (input == 10) {

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

        for (int i = 0; i < 5; i++) {   // prints title ASCII

            mvwprintw(win, 3 + i, 12, "%s", title[i]);

        }


        for (int i = 0; i < 2; i++) {

            int y_pos = 5;
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

        wrefresh(win);

    }

}