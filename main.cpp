#include "ranking/ranking.h"
#include <ncurses.h>
#include <unistd.h>

#define GAMEW
#define SCOREW
#define MENUW

#define GAMEW_PAIR_MAIN 1
#define GAMEW_PAIR_R 2
#define SCOREW_PAIR 3
#define MENUW_PAIR 4
#define BLUE_WHITE 5

int draw_intro();
void draw_map(WINDOW *);
void draw_menu(WINDOW *, int);
void draw_mainpage(WINDOW *, WINDOW *, WINDOW *);
void draw_side(WINDOW *);
void draw_next_blocks(WINDOW *, int);

char *choices[] = {
    "Start",
    "Ranking",
    "exit",
};
int n_choices = sizeof(choices) / sizeof(char *);

int main(int argc, char const *argv[]) {
    WINDOW *intro;
    WINDOW *window1;
    WINDOW *window2;
    WINDOW *window3;

    initscr();
    noecho(); // 입력을 자동으로 화면에 출력하지 않도록 합니다.
    curs_set(FALSE); // cursor를 보이지 않게 합니다.

    if (has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return 1;
    } else {
        start_color();
        init_pair(GAMEW_PAIR_MAIN, COLOR_BLUE, COLOR_WHITE);
        init_pair(GAMEW_PAIR_R, COLOR_RED, COLOR_WHITE);
        init_pair(SCOREW_PAIR, COLOR_BLACK, COLOR_GREEN);
        init_pair(MENUW_PAIR, COLOR_WHITE, COLOR_BLUE);
        init_pair(BLUE_WHITE, COLOR_BLUE, COLOR_WHITE);
    }

    refresh();
    intro = newwin(31, 80, 0, 0);
    window1 = newwin(25, 50, 0, 0);
    window2 = newwin(25, 30, 0, 50);
    window3 = newwin(6, 80, 25, 0);

    wbkgd(window1, COLOR_PAIR(GAMEW_PAIR_MAIN));
    wbkgd(window2, COLOR_PAIR(SCOREW_PAIR));
    wbkgd(window3, COLOR_PAIR(MENUW_PAIR));
    int intro_result;
    while (true) {
        intro_result = draw_intro();
        switch (intro_result) {
        case 0: // 게임 시작
            clear;
            draw_mainpage(window1, window2, window3);
            getchar();
            refresh();
            break;
        case 1: // 랭킹
            init_priority_queue();
            getchar();
            refresh();
            break;
        case 2:
            endwin();
            return 0;
            break;
        }
    }

    endwin();

    return 0;
}

// 게임시작 - 화면 그리기
void draw_mainpage(WINDOW *GAME, WINDOW *SIDE, WINDOW *FOOTER) {
    draw_map(GAME);
    draw_side(SIDE);
    wborder(FOOTER, '|', '|', '-', '-', '+', '+', '+', '+');
    wprintw(FOOTER, "FOOTER BOARD");
    wprintw(SIDE, "SIDE BOARD");
    wrefresh(FOOTER);
}

// 게임시작 - 오른쪽 그리기
void draw_side(WINDOW *SIDE) {
    char *keyList[] = {
        "  ^    :  Up",   "<- ->  :  Left/Right",
        "  v    :  Down", "",
        "SPACE  :  Drop", "K      :  Keep Blocks ",
        "ESC    :  Exit", "",
        "Best   :  ",     "Score  :  ",
        "LEVEL  :  ",
    };
    int n_keyList = sizeof(keyList) / sizeof(char *);

    wborder(SIDE, '|', '|', '-', '-', '+', '+', '+', '+');
    for (int i = 0; i < n_keyList; i++) {
        mvwprintw(SIDE, 2 + i, 4, "%s", keyList[i]);
    }
    wrefresh(SIDE);
    draw_next_blocks(SIDE, n_keyList);
}
// 게임시작 - 오른쪽 subwin (next)
void draw_next_blocks(WINDOW *SIDE, int start_point_y) {
    WINDOW *next_blocks = subwin(SIDE, 10, 26, start_point_y + 3, 52);
    wbkgd(next_blocks, COLOR_PAIR(SCOREW_PAIR));
    // touchwin(SIDE);
    wborder(next_blocks, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(next_blocks, 0, 11, "KEEP");
    wrefresh(next_blocks);
}
// 게임시작 - 게임판 그리기
void draw_map(WINDOW *GAME) {
    static int startpoint_x = 6;
    static int startpoint_y = 4;

    wborder(GAME, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(GAME, 2, 19, "GAME BOARD");
    for (int i = startpoint_y; i <= startpoint_y + 18; i += 2) {
        if ((i - startpoint_y) % 6 == 0) {
            wattron(GAME, COLOR_PAIR(GAMEW_PAIR_MAIN));
            mvwprintw(GAME, i, startpoint_x,
                      "+---+---+---+---+---+---+---+---+---+");
        } else {
            wattron(GAME, COLOR_PAIR(GAMEW_PAIR_R));
            mvwprintw(GAME, i, startpoint_x,
                      "+---+---+---+---+---+---+---+---+---+");
            wattron(GAME, COLOR_PAIR(GAMEW_PAIR_MAIN));
            mvwprintw(GAME, i, startpoint_x, "+");
            mvwprintw(GAME, i, startpoint_x + 12, "+");
            mvwprintw(GAME, i, startpoint_x + 24, "+");
            mvwprintw(GAME, i, startpoint_x + 36, "+");
        }
    }
    for (int i = startpoint_y + 1; i <= startpoint_y + 18; i += 2) {
        wattron(GAME, COLOR_PAIR(GAMEW_PAIR_MAIN));
        mvwprintw(GAME, i, startpoint_x,
                  "|           |           |           |");
        wattron(GAME, COLOR_PAIR(GAMEW_PAIR_R));
        mvwprintw(GAME, i, startpoint_x + 4, "|   |");
        mvwprintw(GAME, i, startpoint_x + 16, "|   |");
        mvwprintw(GAME, i, startpoint_x + 28, "|   |");
    }
    wrefresh(GAME);
}

// 초기화면 그리기
int draw_intro() {
    const int window_size_x = 80;
    const int startpoint_x = 14;
    const int startpoint_y = 7;
    int cursor = 0;
    int choice = -1;
    int c;

    WINDOW *main = newwin(20, window_size_x, 0, 0);
    WINDOW *menu = newwin(11, window_size_x, 20, 0);
    wbkgd(main, COLOR_PAIR(GAMEW_PAIR_R));
    wbkgd(menu, COLOR_PAIR(SCOREW_PAIR));

    wborder(main, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(main, startpoint_y, startpoint_x,
              "#       #   ###   ###   ####    ###   #  #  #   #");
    mvwprintw(main, startpoint_y + 1, startpoint_x,
              "#   #   #  #   # #   #  #   #  #   #  ##    #   #");
    mvwprintw(main, startpoint_y + 2, startpoint_x,
              " # # # #   #   # #   #  #   #  #   #  # #   #   #");
    mvwprintw(main, startpoint_y + 3, startpoint_x,
              "  #   #     ###   ###   ###     ###   #  #   ###");
    mvwprintw(main, 15, 60, "2019203032");
    mvwprintw(main, 16, 60, "2019203013");
    mvwprintw(main, 17, 60, "2017706057");
    mvwprintw(main, 18, 60, "2017742041");

    // cbreak();
    keypad(menu, TRUE);
    wrefresh(main);
    draw_menu(menu, cursor);

    while (1) {
        c = wgetch(menu);
        switch (c) {
        case KEY_LEFT:
            if (cursor == 0)
                cursor = n_choices - 1;
            else
                cursor--;
            break;
        case KEY_RIGHT:
            if (cursor == n_choices - 1)
                cursor = 0;
            else
                cursor++;
            break;
        case 10:
            werase(menu);
            choice = cursor;
            return choice;
            break;
        default:
            mvwprintw(menu, 9, 2, "Select input [ \"<-\", \"ENTER\", \"->\" ]");
            break;
        }
        draw_menu(menu, cursor);
    }
    refresh();
}
// 초기화면 메뉴 그리기
void draw_menu(WINDOW *menu, int highlight) {
    static int y = 5;
    static int x = 12;
    static int cursor = 0;

    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(menu, 2, 38, "menu");
    for (int i = 0; i < n_choices; i++) {
        if (highlight == i) {
            wattron(menu, A_REVERSE);
            mvwprintw(menu, y, x + (2 * x) * i, "%s", choices[i]);
            wattroff(menu, A_REVERSE);
        } else {
            mvwprintw(menu, y, x + (2 * x) * i, "%s", choices[i]);
        }
    }
    wrefresh(menu);
}
