#include "Queue.h"
#include "block.h"
#include "ranking/ranking.h"
#include "score.h"
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
#define BLUE_GRAY 6

#define COLOR_GRAY 8

int draw_intro();
void draw_map(WINDOW *);
void draw_menu(WINDOW *, int);
void draw_mainpage(WINDOW *, WINDOW *, WINDOW *);
void draw_side(WINDOW *);
void draw_keep_blocks(WINDOW *, int, int (*)[5]);
void next_block(WINDOW *, queue<int **> &, int (*)[5]);
void Keyboard(WINDOW *);
void exit_game(WINDOW *, WINDOW *, WINDOW *, queue<int **> &);
void input_name(char *);
void print_score(WINDOW *, int &, int);

char *choices[] = {
    "Start",
    "Ranking",
    "exit",
};
int n_choices = sizeof(choices) / sizeof(char *);

bool flag_enter = false, flag_esc = false;
int x_cursor, y_cursor;

int main(int argc, char const *argv[]) {
    WINDOW *intro;
    WINDOW *window1;
    WINDOW *window2;
    WINDOW *window3;
    queue<int **> blocks;
    int block[5][5] = {
        0,
    };
    char name[33];
    int best_score = get_best_score();
    int score = 0;

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

        init_color(COLOR_GRAY, 500, 500, 500);

        init_pair(GAMEW_PAIR_MAIN, COLOR_BLUE, COLOR_WHITE);
        init_pair(GAMEW_PAIR_R, COLOR_RED, COLOR_WHITE);
        init_pair(SCOREW_PAIR, COLOR_BLACK, COLOR_GREEN);
        init_pair(MENUW_PAIR, COLOR_WHITE, COLOR_BLUE);
        init_pair(BLUE_WHITE, COLOR_BLUE, COLOR_WHITE);
        init_pair(BLUE_GRAY, COLOR_BLUE, COLOR_GRAY);
    }

    refresh();

    // 윈도우 크기 설정
    intro = newwin(31, 80, 0, 0);
    window1 = newwin(25, 50, 0, 0);
    window2 = newwin(25, 30, 0, 50);
    window3 = newwin(9, 80, 25, 0);

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
            input_name(name);
            clear;
            flag_esc = false;
            x_cursor = 8;
            y_cursor = 5;
            draw_mainpage(window1, window2, window3);
            while (1) {
                flag_enter = false;
                next_block(window3, blocks, block); // 큐에서 다음 블록을 받아옴
                draw_keep_blocks(window2, 11, block); // 옆 화면에 블록 출력
                print_score(window2, best_score, score); // 옆 화면에 점수 출력
                Keyboard(window1);
                if (flag_esc)
                    break;
            }
            exit_game(window1, window2, window3,
                      blocks);           // 윈도우 및 queue 초기화
            append_ranking(name, score); // 이름과 점수를 랭킹에 업데이트
            // mvwprintw(window3, 0, 0, "0");
            // wrefresh(window3);
            getchar();
            refresh();
            break;
        case 1: // 랭킹
            init_priority_queue();
            getchar();
            refresh();
            break;
        case 2: // 나가기
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
    draw_map(GAME);  // 게임이 진행되는 화면 그리기
    draw_side(SIDE); // 오른쪽 화면 그리기
    wborder(FOOTER, '|', '|', '-', '-', '+', '+', '+',
            '+'); // 다음 블럭(아래쪽) 화면 테두리 설정
    wprintw(FOOTER, "FOOTER BOARD");
    wprintw(SIDE, "SIDE BOARD");
    wrefresh(FOOTER); // 다음 블럭(아래쪽) 화면 그리기
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

    // 화면 테두리 설정
    wborder(SIDE, '|', '|', '-', '-', '+', '+', '+', '+');
    for (int i = 0; i < n_keyList; i++) {
        mvwprintw(SIDE, 2 + i, 4, "%s", keyList[i]);
    }
    wrefresh(SIDE); // 화면 그리기

    // draw_keep_blocks(SIDE, n_keyList);
}
// 게임시작 - 오른쪽화면 내 다음 보관중인 블럭 출력 subwin (keep)
void draw_keep_blocks(WINDOW *SIDE, int start_point_y, int (*block)[5]) {
    int x, y;
    WINDOW *next_blocks = subwin(SIDE, 11, 26, start_point_y + 2, 52);
    werase(next_blocks);
    wbkgd(next_blocks, COLOR_PAIR(SCOREW_PAIR));
    // touchwin(SIDE);
    wborder(next_blocks, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(next_blocks, 0, 11, "KEEP");

    for (int i = 0; i < 5; i++) {
        x = 8;
        y = i + 3;
        for (int j = 0; j < 5; j++) {
            if (block[i][j] == 0) { // 해당 칸은 블록이 아님
                x += 2;
            } else if ((i % 2 == 1 && j % 2 == 0) ||
                       (i % 2 == 0 && j % 2 == 1)) { // 해당 칸은 블록임
                // 블록은 각 칸을 다른색으로 출력
                wattron(next_blocks, COLOR_PAIR(BLUE_WHITE));
                mvwprintw(next_blocks, y, x, "  ");
                wattron(next_blocks, COLOR_PAIR(MENUW_PAIR));
                x += 2;
            } else { // 해당 칸은 블록임
                wattron(next_blocks, COLOR_PAIR(BLUE_GRAY));
                mvwprintw(next_blocks, y, x, "  ");
                wattron(next_blocks, COLOR_PAIR(MENUW_PAIR));
                x += 2;
            }
        }
    }

    wrefresh(next_blocks);
}
// 게임시작 - 게임판 그리기
void draw_map(WINDOW *GAME) {
    static int startpoint_x = 6;
    static int startpoint_y = 4;

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

    WINDOW *main = newwin(23, window_size_x, 0, 0);  // 로고 화면 생성
    WINDOW *menu = newwin(11, window_size_x, 23, 0); // 메뉴 화면 생성
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

/*
queue에 블록이 빌때마다 5개씩 랜덤으로 추가한다
현재 넣어야 할 블록을 매개변수 block에 반환한다.
*/
void next_block(WINDOW *FOOTER, queue<int **> &blocks, int (*block)[5]) {
    int x;
    int y;
    int count = 0;
    int random;
    int **dynamic_block;

    wbkgd(FOOTER, COLOR_PAIR(MENUW_PAIR));
    werase(FOOTER);

    wborder(FOOTER, '|', '|', '-', '-', '+', '+', '+', '+');
    wprintw(FOOTER, "FOOTER BOARD");

    if (blocks.empty()) { // 가장 처음 호출시 큐가 비어있기 때문에 블록 추가
        srand(time(0));
        Block<int> block1(rand() % 46);
        Block<int> block2(rand() % 46);
        Block<int> block3(rand() % 46);
        Block<int> block4(rand() % 46);
        Block<int> block5(rand() % 46);

        blocks.push(block1.get_dynamic_block());
        blocks.push(block2.get_dynamic_block());
        blocks.push(block3.get_dynamic_block());
        blocks.push(block4.get_dynamic_block());
        blocks.push(block5.get_dynamic_block());
    }

    dynamic_block = blocks.front(); // 가장 앞 블록을 꺼내서 제거
    blocks.pop();

    /* queue에서 꺼낸 블록을 block에 반환, 외부에서 해당 블록 사용 가능 */
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            block[i][j] = dynamic_block[i][j];
        }
    }

    /* 동적으로 할당한 block을 deallocate */
    for (int i = 0; i < 5; i++)
        free(dynamic_block[i]);
    free(dynamic_block);

    if (blocks.empty()) { // 큐에서 마지막 블록을 pop한 경우 다시 큐에 블록
                          // 추가
        Block<int> block1(rand() % 46);
        Block<int> block2(rand() % 46);
        Block<int> block3(rand() % 46);
        Block<int> block4(rand() % 46);
        Block<int> block5(rand() % 46);

        blocks.push(block1.get_dynamic_block());
        blocks.push(block2.get_dynamic_block());
        blocks.push(block3.get_dynamic_block());
        blocks.push(block4.get_dynamic_block());
        blocks.push(block5.get_dynamic_block());
    }

    queue<int **> copy(blocks);

    while (!copy.empty()) {         // FOOTER 윈도우에 블록 모두 출력
        int **block = copy.front(); // front에 있는 블록 저장
        copy.pop();
        for (int i = 0; i < 5; i++) {
            x = 4 * count + 7 + count * 10;
            y = i + 2;
            for (int j = 0; j < 5; j++) {
                if (block[i][j] == 0) { // 해당 칸은 블록이 아님
                    x += 2;
                } else if ((i % 2 == 1 && j % 2 == 0) ||
                           (i % 2 == 0 && j % 2 == 1)) { // 해당 칸은 블록임
                    // 블록은 각 칸을 다른색으로 출력
                    wattron(FOOTER, COLOR_PAIR(BLUE_WHITE));
                    mvwprintw(FOOTER, y, x, "  ");
                    wattron(FOOTER, COLOR_PAIR(MENUW_PAIR));
                    x += 2;
                } else { // 해당 칸은 블록임
                    wattron(FOOTER, COLOR_PAIR(BLUE_GRAY));
                    mvwprintw(FOOTER, y, x, "  ");
                    wattron(FOOTER, COLOR_PAIR(MENUW_PAIR));
                    x += 2;
                }
            }
        }

        count++;
    }

    wrefresh(FOOTER);
}

void Keyboard(WINDOW *GAME) {
    keypad(GAME, TRUE);
    while (1) {
        draw_map(
            GAME); // 지금은 커서 움직임 보기 위해서 보드판을 계속 초기화했음.
        wmove(GAME, y_cursor, x_cursor);
        wprintw(GAME, "o");
        int c = wgetch(GAME);
        switch (c) {
        case 'a':
        case 'A':
            if (x_cursor > 8) {
                wprintw(GAME, " ");
                x_cursor -= 4;
            }
            break;
        case 'd':
        case 'D':
            if (x_cursor < 40) {
                wprintw(GAME, " ");
                x_cursor += 4;
            }
            break;
        case 'w':
        case 'W':
            if (y_cursor > 5) {
                wprintw(GAME, " ");
                y_cursor -= 2;
            }
            break;
        case 's':
        case 'S':
            if (y_cursor < 21) {
                wprintw(GAME, " ");
                y_cursor += 2;
            }
            break;
        case 'k':
        case 'K':
            // 블록 놓기 구현해야 함.
            // 키 입력시 다음 블럭으로 넘어가게만 해 놓았음.
            // 보드에 블록 놓을 시 저장해서 다시 불러오게 하면 될듯합니다.
            flag_enter = true;
            return;
            break;
        case 27:
            // esc 입력시 메뉴 화면으로 나가게 했음.
            // 2~3번 눌러야 나가져서 고칠 예정.
            flag_esc = true;
            return;
            break;
        }
        wrefresh(GAME);
    }
}

void exit_game(WINDOW *GAME, WINDOW *SIDE, WINDOW *FOOTER,
               queue<int **> &blocks) {

    werase(GAME);
    werase(SIDE);
    werase(FOOTER);

    while (!blocks.empty()) {
        blocks.pop();
    }
}

/* 게임 시작시 사용자에게 이름을 입력 받는 함수 */
void input_name(char *name) {
    WINDOW *menu = newwin(11, 80, 23, 0); // 메뉴 화면 생성
    wbkgd(menu, COLOR_PAIR(SCOREW_PAIR)); // 메뉴 화면 색 설정
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwprintw(menu, 5, 15, "input name : ");

    wrefresh(menu);
    echo(); // 입력을 화면에 출력하도록 합니다.

    mvwgetstr(menu, 5, 28, name); // 사용자로부터 이름을 입력 받습니다

    noecho(); // 입력을 자동으로 화면에 출력하지 않도록 합니다.

    werase(menu);
}

/* 옆 화면에 점수를 출력하는 함수 */
void print_score(WINDOW *SIDE, int &best_score, int score) {
    if (score > best_score)
        best_score = score;
    mvwprintw(SIDE, 10, 14, "%d", best_score);
    mvwprintw(SIDE, 11, 14, "%d", score);
    wrefresh(SIDE);
}
