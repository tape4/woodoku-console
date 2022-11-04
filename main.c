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
void draw_map(WINDOW *GAME);
void draw_menu(WINDOW *MENU, int);
void draw_mainpage(WINDOW *, WINDOW *, WINDOW *);
void draw_side(WINDOW *);
char *choices[] = {"Start", "Ranking", "exit",};
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
    int intro_result = draw_intro();
    switch(intro_result) {
	    case 0:
		    clear;
		    draw_mainpage(window1, window2, window3);
		    //draw_map(window1);
		    //wrefresh(window2);
		    //wrefresh(window3);
		    getchar();
		    refresh();
		    break;
	    case 1: 
		    break;
	    case 2:
		    endwin();
		    return 0;
		    break;
    }

    endwin();

    return 0;
}

void draw_mainpage(WINDOW *GAME, WINDOW *SIDE, WINDOW *FOOTER) {
	draw_map(GAME);
	draw_side(SIDE);
    	wborder(FOOTER, '|', '|', '-', '-', '+', '+', '+', '+');
        wprintw(FOOTER, "FOOTER BOARD");
        wprintw(SIDE, "SIDE BOARD");
	wrefresh(FOOTER);
}
void draw_side(WINDOW *SIDE) {
    	wborder(SIDE, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(SIDE, 2, 1, " ↑ : Up");
	mvwprintw(SIDE, 3, 1, "← →: Left/Right");
	mvwprintw(SIDE, 4, 1,  " ↓ : Down");
	wrefresh(SIDE);
}
void draw_map(WINDOW *GAME) {
    static int startpoint_x = 6;
    static int startpoint_y = 3;

    wborder(GAME, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(GAME, 1, 19, "GAME BOARD");
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

// 처음화면 그리기
int draw_intro() {
    static int window_size_x = 70;
    static int startpoint_x = 9;
    static int startpoint_y = 7;
    int cursor = 0;
    int choice = -1;
    int c;

    WINDOW *main = newwin(20, window_size_x, 0, 0);
    WINDOW *menu = newwin(11, window_size_x, 20, 0);
    wbkgd(main, COLOR_PAIR(GAMEW_PAIR_R));
    wbkgd(menu, COLOR_PAIR(SCOREW_PAIR));

    wborder(main, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(main, startpoint_y, startpoint_x, "#       #   ###   ###   ####   #   #  #  #  #   #");
    mvwprintw(main, startpoint_y+1, startpoint_x, "#   #   #  #   # #   #  #   #  #   #  ##    #   #");
    mvwprintw(main, startpoint_y+2, startpoint_x, " # # # #   #   # #   #  #   #  #   #  # #   #   #");
    mvwprintw(main, startpoint_y+3, startpoint_x, "  #   #     ###   ###   ###     ###   #  #   ###");
    mvwprintw(main, 15, 50, "2019203032");
    mvwprintw(main, 16, 50, "2019203013");
    mvwprintw(main, 17, 50, "2017706057");
    mvwprintw(main, 18, 50, "2017742041");

    //mvwprintw(menu, 2, window_size_x/2-4, "menu");
    //mvwprintw(menu, 5, 10, "start");
    //mvwprintw(menu, 5, 30, "ranking");
    //mvwprintw(menu, 5, 50, "exit");

    //cbreak();
    keypad(menu, TRUE);
    wrefresh(main);
    draw_menu(menu, cursor);

    while(1)
    {
	c = wgetch(menu);
	switch(c){
		case KEY_LEFT:
			if(cursor == 0) cursor = n_choices-1;
			else cursor--;
			break;
		case KEY_RIGHT:
			if(cursor == n_choices-1) cursor = 0;
			else cursor++;
			break;
		case 10:
			werase(menu);
			choice = cursor;
			return choice;
			break;
		default:
			mvwprintw(menu, 9, 2, "Select input [ \"<-\" \"ENTER\" \"->\" ]");
			break;	
	}
	//if (choice == 2) break;//return choice;
	draw_menu(menu, cursor);
    }
    refresh();
}

void draw_menu(WINDOW *menu, int highlight) {
    static int y = 5;
    static int x = 10;
    static int cursor = 0;

    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(menu, 2, 31, "menu");
    for(int i=0; i<n_choices; i++) {
	    if(highlight == i) {
		    wattron(menu, A_REVERSE);
		    mvwprintw(menu, y, x+(2*x)*i, "%s", choices[i]);
		    wattroff(menu, A_REVERSE);
	    } else {
		    mvwprintw(menu, y, x+(2*x)*i, "%s", choices[i]);
	    }
    }
    wrefresh(menu);
}
