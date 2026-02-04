#include "game_over.h"
#include "highscore.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <cstdlib>
#include <cstring>
#include <cctype>


void game_over_screen(WINDOW *win, int lives, int score, bool times_up) {

    const char *text_lose[5] = {
        "__   __          ___  _        _ _ ",
       R"(\ \ / /__ _  _  |   \(_)___ __| | |)",
       R"( \ V / _ \ || | | |) | / -_) _` |_|)",
       R"(  |_|\___/\_,_| |___/|_\___\__,_(_))",
        "                                   "
    };

    const char *text_win[5] = {
        "__   __         __      __ _      _ ",
      R"(\ \ / /__ _  _  \ \    / /(_)_ _ | |)",
      R"( \ V / _ \ || |  \ \/\/ / | | ' \|_|)",
      R"(  |_|\___/\_,_|   \_/\_/  |_|_||_(_))",
        "                                    "
  };

    const char *text_times_up[5] = {
    " _____ _            _                _ ",
    "|_   _(_)_ __  ___ ( )___  _  _ _ __| |",
   R"(  | | | | '  \/ -_| /(_-< | || | '_ \_|)",
   R"(  |_| |_|_|_|_\___/  /__/  \_,_| .__(_))",
    "                               |_|     "
  };

    int screen_width, screen_height;
    getmaxyx(win, screen_height, screen_width);
    if (screen_width == 1 || screen_height == 1) {
        screen_width = COLS;
        screen_height = LINES;
    }

    int dialog_width = 80;
    int dialog_height = 18;

    WINDOW *dialog = newwin(dialog_height, dialog_width, screen_height / 2 - dialog_height / 2, screen_width / 2 - dialog_width / 2);
    nodelay(dialog, FALSE);

    box(dialog, 0, 0);

    //wattron(dialog, A_BLINK);

    for (int i = 0; i < 5; i++) {   // prints game over message

        if (lives <= 0) {
            mvwprintw(dialog, 2 + i, dialog_width/2 - strlen(text_lose[i]) / 2, "%s", text_lose[i]);
        } else if (times_up) {
            mvwprintw(dialog, 2 + i, dialog_width/2 - strlen(text_win[i]) / 2, "%s", text_times_up[i]);
        } else {
            mvwprintw(dialog, 2 + i, dialog_width/2 - strlen(text_win[i]) / 2, "%s", text_win[i]);
        }

    }

    wattroff(dialog, A_BLINK);

    wattron(dialog, A_BOLD);
    mvwprintw(dialog, 9, dialog_width/2 - 6, "score: %d", score);
    wattroff(dialog, A_BOLD);

    mvwprintw(dialog, dialog_height / 2 + 4, dialog_width / 2 - 18, "Insert Nickname:");

    wrefresh(dialog);

    WINDOW* input_box = newwin(3, 18, screen_height / 2 + 3, screen_width / 2);
    box(input_box, 0, 0);
    wrefresh(input_box);

    char name[16];
    int i = 0;
    int ch;

    memset(name, 0, sizeof(name));
    curs_set(1);
    wmove(input_box, 1, i + 1);

    while (true) {
        ch = wgetch(input_box);

        if (ch == 10 || ch == KEY_ENTER) {

            name[i] = '\0';
            break;

        }

        if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
            if (i > 0) {
                i--;
                mvwaddch(input_box, 1, i + 1, ' ');
                wmove(input_box, 1, i + 1);
            }
        }

         if (i < 16 && isprint(ch)) {
            name[i] = (char)ch;
            i++;
            mvwaddch(input_box, 1, i, ch);
            wmove(input_box, 1, i + 1);
        }

        wrefresh(input_box);

    }

    if (name[0] != '\0') save_highscore(name, score);
    curs_set(0);

    delwin(input_box);
    delwin(dialog);

}


