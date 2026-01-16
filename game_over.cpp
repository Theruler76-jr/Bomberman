#include "game_over.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <cstdlib>
#include <cstring>

#include "highscore.h"

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
    char name[16] = "nuovonickname";

    while (true) {

        input = wgetch(dialog);

        if (input == 10) {
            save_highscore(name, score);
            break;
        }

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


