#include "Map.h"
#include "game.h"
#include "Bomb.h"

#ifdef _WIN32
    #include <ncurses/ncurses.h> // Percorso per Windows/MinGW
#else
    #include <ncurses.h>         // Percorso standard per Linux
#endif

#include <iostream>
#include <cmath>

#define COLOR_GRAY 8


/*LEGENDA MAPPA:
 I -> muro indistruttibile
 m -> muro distruttibile
 v -> vuoto
 @ -> player
 $ -> bomba
 R/L/N/T/P -> item sotto un muro
 r/l/n/t/p -> item nel vuoto
 # -> nemico base
 % -> nemico forte (sul vuoto)
 x -> nemico forte (sul muro distruttibile)
 z -> nemico forte (sul muro indistruttibile)
*/


Map :: Map () {
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            if (i==0 || j==0 || i==(row-1) || j==col-1) {
                map[i][j]=muro_ind;
            }
            else if ((i+j)%2==0 && i%2==0) {
                map[i][j]=muro_ind;
            }
            else if (i==1 || j==1 || i==(row-2) || j==(col-2)) {
                map[i][j]=vuoto;
            }
            else {
                map[i][j]=vuoto;
            }
            map[10][0]=vuoto;
            map[10][40]=vuoto;
        }
    }
}

void Map::livello(int lv) {
    int n_muri=(int)(120.0*sqrt(lv));
    while (n_muri>0){
        int x=rand()%39+1;
        int y=rand()%19+1;
        if ((x!=1 || y!=10) && (x!=1 || y!=9) && (x!=2 || y!=9) && map[y][x]==vuoto) {
            map[y][x]=muro;
            n_muri--;
        }
    }
    if (lv==1) {
        map[10][0]=muro_ind;
        map[1][1]=vuoto;
        map[2][1]=vuoto;
        map[1][2]=vuoto;
    }
    if (lv==5) {
        map[10][40]=muro_ind;
    }
}
 //Player pl, Item it, Bomb b, enemy en
void Map::stamp(WINDOW *win, int x_start, int y_start) {
    start_color();
    init_color(COLOR_GRAY,574,574,574);
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    init_pair(2,COLOR_GRAY,COLOR_GRAY);
    init_pair(3,COLOR_BLACK,COLOR_BLACK);
    init_pair(4,COLOR_WHITE,COLOR_BLACK);
    init_pair(5,COLOR_RED,COLOR_BLACK);
    init_pair(6,COLOR_RED,COLOR_GRAY);
    init_pair(7,COLOR_RED,COLOR_WHITE);
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            if (map[i][j]==muro_ind) { //muro indistruttibile (bianco)
                wattron(win,COLOR_PAIR(1));
                mvwaddch(win,i+y_start,j+x_start,ACS_BLOCK);
                wattroff(win,COLOR_PAIR(1));
            }
            else if (map[i][j]==muro || map[i][j]==item_wall_R || map[i][j]==item_wall_L || map[i][j]==item_wall_N || map[i][j]==item_wall_P || map[i][j]==item_wall_T) { //muro distruttibile (grigio)
                wattron(win,COLOR_PAIR(2));
                mvwaddch(win,i+y_start,j+x_start,ACS_CKBOARD);
                wattroff(win,COLOR_PAIR(2));
            }
            else if (map[i][j]==vuoto){ //vuoto (nero)
                wattron(win,COLOR_PAIR(3));
                mvwaddch(win,i+y_start,j+x_start,' ');
                wattroff(win,COLOR_PAIR(3));
            }
            else if (map[i][j]==player_skin) { //player
                wattron(win,COLOR_PAIR(4));
                mvwaddch(win,i+y_start,j+x_start,player_skin);
                wattroff(win,COLOR_PAIR(4));
            }
            else if (map[i][j]==bomb_skin || map[i][j]==bomb_exp) { //bomba
                wattron(win,COLOR_PAIR(4));
                mvwaddch(win,i+y_start,j+x_start,ACS_LANTERN);
                wattroff(win,COLOR_PAIR(4));
            }
            else if (map[i][j]==item_r) { //item con muro distrutto
                wattron(win,COLOR_PAIR(4));
                mvwaddch(win,i+y_start,j+x_start,item_wall_R);
                wattroff(win,COLOR_PAIR(4));
            }
            else if (map[i][j]==item_l) { //item con muro distrutto
                wattron(win,COLOR_PAIR(4));
                mvwaddch(win,i+y_start,j+x_start,item_wall_L);
                wattroff(win,COLOR_PAIR(4));
            }
            else if (map[i][j]==item_n) { //item con muro distrutto
                wattron(win,COLOR_PAIR(4));
                mvwaddch(win,i+y_start,j+x_start,item_wall_N);
                wattroff(win,COLOR_PAIR(4));
            }
            else if (map[i][j]==item_t) { //item con muro distrutto
                wattron(win,COLOR_PAIR(4));
                mvwaddch(win,i+y_start,j+x_start,item_wall_T);
                wattroff(win,COLOR_PAIR(4));
            }
            else if (map[i][j]==item_p) { //item con muro distrutto
                wattron(win,COLOR_PAIR(4));
                mvwaddch(win,i+y_start,j+x_start,item_wall_P);
                wattroff(win,COLOR_PAIR(4));
            }
            else if (map[i][j]==base_en) { //nemico base
                wattron(win,COLOR_PAIR(5));
                mvwaddch(win,i+y_start,j+x_start,base_en);
                wattroff(win,COLOR_PAIR(5));
            }
            else if (map[i][j]==adv_enemy_vuoto) { //nemico forte su vuoto
                wattron(win,COLOR_PAIR(5));
                mvwaddch(win,i+y_start,j+x_start,adv_enemy_vuoto);
                wattroff(win,COLOR_PAIR(5));
            }
            else if (map[i][j]==adv_enemy_muro) { //nemico forte su muro
                wattron(win,COLOR_PAIR(6));
                mvwaddch(win,i+y_start,j+x_start,adv_enemy_vuoto);
                wattroff(win,COLOR_PAIR(6));
            }
            else if (map[i][j]==adv_enemy_muro_ind) { //nemico forte su muro indistruttibile
                wattron(win,COLOR_PAIR(7));
                mvwaddch(win,i+y_start,j+x_start,adv_enemy_vuoto);
                wattroff(win,COLOR_PAIR(7));
            }
        }
    }
}

char Map::pos (int x, int y) {
    if (x<0 || x>=col || y<0 || y>=row) {
        return('['); //carattere random per segnalare errore
    }
    return(map[y][x]);
}

void Map::cambia(int x, int y, char nuovo) {
    if (x>=0 && x<col && y>=0 && y<row) {
        map[y][x]=nuovo;
    }
}

//test per stampare i livelli

/*
int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    srand(time(0));
    Map x;
    int lv=5;
    x.livello(lv);
    WINDOW *win=newwin(40,80,0,0);
    refresh();
    x.stamp(win,0,0);
    wrefresh(win);
    getch();
    endwin();
}*/