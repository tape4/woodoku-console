#include "Queue.h"
<<<<<<< HEAD
#include "block.h"
#include "ranking/ranking.h"
#include <ncurses.h>
#include <unistd.h>
=======
#include "ranking/ranking.h"
#include <ncurses.h>
#include <unistd.h>

>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
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
<<<<<<< HEAD
WINDOW *draw_mainpage(WINDOW *, WINDOW *, WINDOW *);
WINDOW *draw_side(WINDOW *);
WINDOW *draw_keep_blocks(WINDOW *, int);

template <class Item>
void draw_side_box(WINDOW *win, int y, int x, Block<Item> &blc);
template <class Item>
void draw_game_box(WINDOW *win, int y, int x, Block<Item> &blc);

char *choices[] = {
    const_cast<char *>("Start"),
    const_cast<char *>("Ranking"),
    const_cast<char *>("exit"),
=======
void draw_mainpage(WINDOW *, WINDOW *, WINDOW *);
void draw_side(WINDOW *);
void draw_keep_blocks(WINDOW *, int);
int *next_block(WINDOW *FOOTER, queue<int (*)[5]> &blocks);

char *choices[] = {
    "Start",
    "Ranking",
    "exit",
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
};
int n_choices = sizeof(choices) / sizeof(char *);

int main(int argc, char const *argv[]) {
<<<<<<< HEAD
    // queue<Block<BYTE>> que;

    Block<BYTE> blc;
    Block<BYTE> blc1;
    Block<BYTE> blc2;

    // que.push(blc);
    // que.push(blc1);
    // que.push(blc2);
=======
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
    WINDOW *intro;
    WINDOW *window1;
    WINDOW *window2;
    WINDOW *window3;
<<<<<<< HEAD
    WINDOW *next_blocks;
=======

>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
    initscr();
    noecho(); // 입력을 자동으로 화면에 출력하지 않도록 합니다.
    curs_set(FALSE); // cursor를 보이지 않게 합니다.

    // 터미널 색 설정
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

    // 윈도우 크기 설정
    intro = newwin(31, 80, 0, 0);
    window1 = newwin(25, 50, 0, 0);
    window2 = newwin(25, 30, 0, 50);
<<<<<<< HEAD
    window3 = newwin(6, 80, 25, 0);
=======
    window3 = newwin(9, 80, 25, 0);
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517

    // 윈도우 색 설정
    wbkgd(window1, COLOR_PAIR(GAMEW_PAIR_MAIN));
    wbkgd(window2, COLOR_PAIR(SCOREW_PAIR));
    wbkgd(window3, COLOR_PAIR(MENUW_PAIR));
    int intro_result;

    // 메인화면
    while (true) {
        intro_result = draw_intro(); // 메인화면 그리기
        switch (intro_result) { // 메인화면 선택에 따라 다른 화면 출력
        case 0:                 // 게임 시작
            clear;
<<<<<<< HEAD
            next_blocks = draw_mainpage(window1, window2, window3);
            getchar();
            refresh();

            break;
        case 1: // 랭킹
            init_priority_queue();
=======
            draw_mainpage(window1, window2, window3);
            getchar();
            refresh();
            break;
        case 1: // 랭킹
            // init_priority_queue();
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
            getchar();
            refresh();
            break;
        case 2: // 나가기
            endwin();
            return 0;
            break;
        }
<<<<<<< HEAD
    } //
    // WINDOW *win1 = subwin(window1, 5, 5, 5, 5);
    // Block<BYTE> blc5;
    // blc5.get_random_block();
    // draw_side_box(win1, 1, 1, blc5);
    // wrefresh(win1);

    // WINDOW *win2 = subwin(window2, 5, 5, 5, 5);
    // Block<BYTE> blc10;
    // blc10.get_random_block();
    // draw_side_box(window2, 2, 5, blc10);
    // mvwprintw(window2, 1, 0, "-----");
    // touchwin(window2);
    // wrefresh(window2);
    // Block<BYTE> blc5;
    // draw_side_box(next_blocks, 2, 2, blc5);
    // mvwprintw(next_blocks, 0, 0, "abcjsjwme");
    wrefresh(next_blocks);
=======
    }
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517

    endwin();
    return 0;
}

// 게임시작 - 화면 그리기
<<<<<<< HEAD

WINDOW *draw_mainpage(WINDOW *GAME, WINDOW *SIDE, WINDOW *FOOTER) {
    draw_map(GAME); // 게임이 진행되는 화면 그리기
    // draw_side(SIDE); // 오른쪽 화면 그리기
=======
void draw_mainpage(WINDOW *GAME, WINDOW *SIDE, WINDOW *FOOTER) {
    draw_map(GAME);  // 게임이 진행되는 화면 그리기
    draw_side(SIDE); // 오른쪽 화면 그리기
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
    wborder(FOOTER, '|', '|', '-', '-', '+', '+', '+',
            '+'); // 다음 블럭(아래쪽) 화면 테두리 설정
    wprintw(FOOTER, "FOOTER BOARD");
    wprintw(SIDE, "SIDE BOARD");
    wrefresh(FOOTER); // 다음 블럭(아래쪽) 화면 그리기
<<<<<<< HEAD
    return draw_side(SIDE);
}

// 게임시작 - 오른쪽 그리기
WINDOW *draw_side(WINDOW *SIDE) {
    char *keyList[] = {
        const_cast<char *>("  ^    :  Up"),
        const_cast<char *>("<- ->  :  Left/Right"),
        const_cast<char *>("  v    :  Down"),
        const_cast<char *>(""),
        const_cast<char *>("SPACE  :  Drop"),
        const_cast<char *>("K      :  Keep Blocks "),
        const_cast<char *>("ESC    :  Exit"),
        const_cast<char *>(""),
        const_cast<char *>("Best   :  "),
        const_cast<char *>("Score  :  "),
        const_cast<char *>("LEVEL  :  "),
=======
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
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
    };
    int n_keyList = sizeof(keyList) / sizeof(char *);

    // 화면 테두리 설정
    wborder(SIDE, '|', '|', '-', '-', '+', '+', '+', '+');
    for (int i = 0; i < n_keyList; i++) {
        mvwprintw(SIDE, 2 + i, 4, "%s", keyList[i]);
    }
    wrefresh(SIDE); // 화면 그리기
<<<<<<< HEAD
    return draw_keep_blocks(SIDE, n_keyList);
}
// 게임시작 - 오른쪽화면 내 다음 보관중인 블럭 출력 subwin (keep)

WINDOW *draw_keep_blocks(WINDOW *SIDE, int start_point_y) {
=======

    draw_keep_blocks(SIDE, n_keyList);
}
// 게임시작 - 오른쪽화면 내 다음 보관중인 블럭 출력 subwin (keep)
void draw_keep_blocks(WINDOW *SIDE, int start_point_y) {
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
    WINDOW *next_blocks = subwin(SIDE, 10, 26, start_point_y + 3, 52);
    wbkgd(next_blocks, COLOR_PAIR(SCOREW_PAIR));
    // touchwin(SIDE);
    wborder(next_blocks, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(next_blocks, 0, 11, "KEEP");
    wrefresh(next_blocks);
<<<<<<< HEAD

    // keep block 화면에 블럭 그리기
    Block<BYTE> blc;
    draw_side_box(next_blocks, 2, 5, blc);
    wrefresh(next_blocks);
    return next_blocks;
}

=======
}
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
// 게임시작 - 게임판 그리기
void draw_map(WINDOW *GAME) {
    static int startpoint_x = 6;
    static int startpoint_y = 4;
<<<<<<< HEAD
    int c = 0;
=======
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517

    wborder(GAME, '|', '|', '-', '-', '+', '+', '+', '+'); // 화면 테두리 설정
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

    WINDOW *main = newwin(20, window_size_x, 0, 0);  // 로고 화면 생성
    WINDOW *menu = newwin(11, window_size_x, 20, 0); // 메뉴 화면 생성
    wbkgd(main, COLOR_PAIR(GAMEW_PAIR_R));           // 로고 화면 색 설정
    wbkgd(menu, COLOR_PAIR(SCOREW_PAIR));            // 메뉴 화면 색 설정

    // 로고 화면 테두리 설정
    wborder(main, '|', '|', '-', '-', '+', '+', '+', '+');

    // 로고 그리기
    mvwprintw(main, startpoint_y, startpoint_x,
              "#       #   ###   ###   ####    ###   #  #  #   #");
    mvwprintw(main, startpoint_y + 1, startpoint_x,
              "#   #   #  #   # #   #  #   #  #   #  ##    #   #");
    mvwprintw(main, startpoint_y + 2, startpoint_x,
              " # # # #   #   # #   #  #   #  #   #  # #   #   #");
    mvwprintw(main, startpoint_y + 3, startpoint_x,
              "  #   #     ###   ###   ###     ###   #  #   ###");

    // 학번을 적었는데 한글이 출력이안되서 고민중입니다.
    mvwprintw(main, 15, 60, "2019203032");
    mvwprintw(main, 16, 60, "2019203013");
    mvwprintw(main, 17, 60, "2017706057");
    mvwprintw(main, 18, 60, "2017742041");

    // cbreak();
    keypad(menu, TRUE);
    wrefresh(main);
    draw_menu(menu, cursor);

    // 키보드 입력받기
    while (1) {
        c = wgetch(menu);
        switch (c) {
            // 왼쪽
        case KEY_LEFT:
            if (cursor == 0)
                cursor = n_choices - 1;
            else
                cursor--;
            break;
            // 오른쪽
        case KEY_RIGHT:
            if (cursor == n_choices - 1)
                cursor = 0;
            else
                cursor++;
            break;
            // 엔터 (=10)
        case 10:
            werase(menu);
            choice = cursor;
            return choice;
            break;
            // 그외
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

    // 메뉴화면 테두리 설정
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(menu, 2, 38, "menu");
    for (int i = 0; i < n_choices; i++) {
        // 현재 커서 값에 따라 메뉴 색 다르게 출력
        // 해당 색 이면 다르게 출력
        if (highlight == i) {
            wattron(menu, A_REVERSE); // 색 설정
            mvwprintw(menu, y, x + (2 * x) * i, "%s", choices[i]);
            wattroff(menu, A_REVERSE); // 색 설정 끄기
        } else {
            // 커서가 아닌 다른 메뉴는 그대로 출력
            mvwprintw(menu, y, x + (2 * x) * i, "%s", choices[i]);
        }
    }
    wrefresh(menu);
}

<<<<<<< HEAD
template <class Item>
void draw_side_box(WINDOW *win, int y, int x, Block<Item> &blc) {
    blc.draw_box(win, y + 1, x + 3);
}
template <class Item>
void draw_game_box(WINDOW *win, int y, int x, Block<Item> &blc) {
    blc.draw_box(win, y, x);
=======
/*
    [Usage]
    queue<int(*)[5]> blocks;
    int(*block)[5];
    block = (int(*)[5])next_block(window3, blocks);
    // block[i][j] 로 접근

*/
int *next_block(WINDOW *FOOTER, queue<int (*)[5]> &blocks) {
    int x;
    int y;
    int count = 0;
    int(*block)[5];

    wbkgd(FOOTER, COLOR_PAIR(MENUW_PAIR));
    werase(FOOTER);

    wborder(FOOTER, '|', '|', '-', '-', '+', '+', '+', '+');
    wprintw(FOOTER, "FOOTER BOARD");

    if (blocks.empty()) { // 가장 처음 호출시 큐가 비어있기 때문에 블록 추가
        // 블록 객체를 랜덤으로 받는 코드로 추후 업그레이드 필요
        int block1[5][5] = {{0, 0, 1, 0, 0},
                            {0, 0, 1, 0, 0},
                            {0, 0, 1, 0, 0},
                            {0, 0, 1, 0, 0},
                            {0, 0, 1, 0, 0}};

        int block2[5][5] = {{0, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0},
                            {0, 1, 0, 0, 0},
                            {0, 1, 1, 1, 0},
                            {0, 0, 0, 0, 0}};

        int block3[5][5] = {{0, 0, 0, 0, 0},
                            {0, 0, 1, 0, 0},
                            {0, 1, 1, 1, 0},
                            {0, 0, 1, 0, 0},
                            {0, 0, 0, 0, 0}};

        int block4[5][5] = {{0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0},
                            {1, 1, 1, 1, 1},
                            {0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0}};

        int block5[5][5] = {{0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0},
                            {0, 1, 1, 1, 0},
                            {0, 0, 0, 0, 0}};

        blocks.push(block1);
        blocks.push(block2);
        blocks.push(block3);
        blocks.push(block4);
        blocks.push(block5);
    }

    block = blocks.front(); // 반환할 블록
    blocks.pop();

    if (blocks.empty()) { // 큐에서 마지막 블록을 pop한 경우 다시 큐에 블록 추가
        // 블록 객체를 랜덤으로 받는 코드로 추후 업그레이드 필요
        int block1[5][5] = {{0, 0, 1, 0, 0},
                            {0, 0, 1, 0, 0},
                            {0, 0, 1, 0, 0},
                            {0, 0, 1, 0, 0},
                            {0, 0, 1, 0, 0}};

        int block2[5][5] = {{0, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0},
                            {0, 1, 0, 0, 0},
                            {0, 1, 1, 1, 0},
                            {0, 0, 0, 0, 0}};

        int block3[5][5] = {{0, 0, 0, 0, 0},
                            {0, 0, 1, 0, 0},
                            {0, 1, 1, 1, 0},
                            {0, 0, 1, 0, 0},
                            {0, 0, 0, 0, 0}};

        int block4[5][5] = {{0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0},
                            {1, 1, 1, 1, 1},
                            {0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0}};

        int block5[5][5] = {{0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0},
                            {0, 1, 1, 1, 0},
                            {0, 0, 0, 0, 0}};

        blocks.push(block1);
        blocks.push(block2);
        blocks.push(block3);
        blocks.push(block4);
        blocks.push(block5);
    }

    queue<int(*)[5]> copy(blocks);

    while (!copy.empty()) { // FOOTER 윈도우에 블록 모두 출력
        int(*block)[5] = copy.front(); // front에 있는 블록 저장
        copy.pop();
        for (int i = 0; i < 5; i++) {
            x = 4 * count + 7 + count * 10;
            y = i + 2;
            for (int j = 0; j < 5; j++) {
                if (block[i][j] == 0) { // 해당 칸은 블록이 아님
                    x += 2;
                } else { // 해당 칸은 블록임
                    // 블록은 다른색으로 출력
                    wattron(FOOTER, COLOR_PAIR(GAMEW_PAIR_MAIN));
                    mvwprintw(FOOTER, y, x, "  ");
                    wattron(FOOTER, COLOR_PAIR(MENUW_PAIR));
                    x += 2;
                }
            }
        }

        count++;
    }

    wrefresh(FOOTER);

    return (int *)block;
>>>>>>> b24603e83b36714c6ea61aa30f203da8e93d7517
}
