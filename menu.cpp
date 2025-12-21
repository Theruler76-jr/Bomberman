#include "menu.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <stdlib.h>
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

    int input;
    const char *menu[3] {"New Game", "Leaderboard", "Quit"};
    int selection = 0;

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    while (true) {

        input = getch();

        switch (input) {
            case 'q':
                return 'Q';

            case KEY_UP:
                if (selection > 0) selection--;
                break;

            case KEY_DOWN:
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


        box(win, 0, 0);

        mvwprintw(win, 0, width/2 - 2, "MENU");

        for (int i = 0; i < 7; i++) {

            mvwprintw(win, 3 + i, 60 - strlen(title[i]) / 2, "%s", title[i]);

        }


        for (int i = 0; i < 3; i++) {

            if (selection == i) {
                wattron(win, COLOR_PAIR(1));
                wattron(win, A_BOLD);
            }


            mvwprintw(win, 16 + i, 40 - strlen(menu[i]) / 2, "%s", menu[i]);

            wattroff(win, COLOR_PAIR(1));
            wattroff(win, A_BOLD);

        }

        //mvwprintw(win, 0, 0, "%d, %d", width, height);

        wrefresh(win);
        //refresh();
    }

}