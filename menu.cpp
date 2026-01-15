#include "menu.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <cstdlib>
#include <cstring>

char menu_loop(WINDOW *win) {

    const char *title[7] = {
        ":::::::::   ::::::::  ::::    ::::  :::::::::  :::::::::: :::::::::  ::::    ::::      :::     ::::    :::",
        ":+:    :+: :+:    :+: +:+:+: :+:+:+ :+:    :+: :+:        :+:    :+: +:+:+: :+:+:+   :+: :+:   :+:+:   :+:",
        "+:+    +:+ +:+    +:+ +:+ +:+:+ +:+ +:+    +:+ +:+        +:+    +:+ +:+ +:+:+ +:+  +:+   +:+  :+:+:+  +:+",
        "+#++:++#+  +#+    +:+ +#+  +:+  +#+ +#++:++#+  +#++:++#   +#++:++#:  +#+  +:+  +#+ +#++:++#++: +#+ +:+ +#+",
        "+#+    +#+ +#+    +#+ +#+       +#+ +#+    +#+ +#+        +#+    +#+ +#+       +#+ +#+     +#+ +#+  +#+#+#",
        "#+#    #+# #+#    #+# #+#       #+# #+#    #+# #+#        #+#    #+# #+#       #+# #+#     #+# #+#   #+#+#",
        "#########   ########  ###       ### #########  ########## ###    ### ###       ### ###     ### ###    ####"
    };

    keypad(win, TRUE);

    int width, height;
    getmaxyx(win, height, width);
    if (width == 1 || height == 1) {
        width = 120;
        height = 30;
    }

    int input;
    const char *menu[3] = {"New Game", "Leaderboard", "Quit"};
    int selection = 0;

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    while (true) {

        input = getch();

        switch (input) {

            case KEY_UP:
                if (selection > 0) selection--;
                break;

            case KEY_DOWN:
                if (selection < 2) selection++;
                break;

            case 'w':
                if (selection > 0) selection--;
                break;

            case 's':
                if (selection < 2) selection++;
                break;

            case 'W':
                if (selection > 0) selection--;
                break;

            case 'S':
                if (selection < 2) selection++;
                break;

            case 10:

                switch (selection) {
                    case 0:
                        return 'G';
                    case 1:
                        return 'H';
                    case 2:
                        return 'Q';
                    default:
                        return 'E';
                }

            default:
                break;
        }


        box(win, '!', '=');

        //mvwprintw(win, 0, width/2 - 2, "MENU");

        for (int i = 0; i < 7; i++) {   // prints title ASCII

            mvwprintw(win, 3 + i, width/2 - strlen(title[i]) / 2, "%s", title[i]);

        }


        for (int i = 0; i < 3; i++) {   // prints menu buttons

            mvwprintw(win, 16 + i*2, width/2 - strlen(menu[i]) / 2 - 2, " ");

            if (selection == i) {
                mvwprintw(win, 16 + i*2, width/2 - strlen(menu[i]) / 2 - 2, ">");
                wattron(win, COLOR_PAIR(1));
                wattron(win, A_BOLD);
            }


            mvwprintw(win, 16 + i*2, width/2 - strlen(menu[i]) / 2, "%s", menu[i]);

            wattroff(win, COLOR_PAIR(1));
            wattroff(win, A_BOLD);

        }

        //mvwprintw(win, 0, 0, "%d, %d", width, height);

        wrefresh(win);
        //refresh();
    }

}