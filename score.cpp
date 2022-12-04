#include "score.h"

/* 9*9 배열인 game_board를 받아서 다 찬 칸을 0으로 만든다
   점수를 계산해서 score에 반환 */
void check_board(int (*game_board)[9], int &score) {
    int i, j;
    bool is_fill;          // 9칸이 찼는지를 저장
    int reduplication = 0; // 한번에 블록을 다 채운 중복 횟수

    bool row[9] = {
        // 몇번째 가로가 다 찼는지를 저장
        false,
    };
    bool col[9] = {
        // 몇번째 세로가 다 찼는지를 저장
        false,
    };

    // 정사각형이 다 찼는지는 마지막에 검사하므로 바로 0으로 만든다

    /* 가로로 9줄이 다 찼는지 검사 */
    for (i = 0; i < 9; i++) {
        is_fill = true;

        for (j = 0; j < 9; j++) {
            if (game_board[i][j] == 0) {
                is_fill = false;
                break;
            }
        }

        if (is_fill == true) {
            reduplication++;
            row[i] = true; // 몇번째 가로가 다 찼는지를 저장
        }
    }

    /* 세로로 9줄이 다 찼는지 검사 */
    for (j = 0; j < 9; j++) {
        is_fill = true;

        for (i = 0; i < 9; i++) {
            if (game_board[i][j] == 0) {
                is_fill = false;
                break;
            }
        }

        if (is_fill == true) {
            reduplication++;
            col[j] = true;
        }
    }

    /* 정사각형 9칸이 다 찼는지 검사 */

    for (int y = 0; y < 9; y += 3) {
        for (int x = 0; x < 9; x += 3) {
            is_fill = true;

            for (i = y; i < y + 3; i++) {
                for (j = x; j < x + 3; j++) {
                    if (game_board[i][j] == 0) {
                        is_fill = false;
                    }
                }
            }

            if (is_fill == true) { // 해당 정사각형이 다 찬 경우 다시 0으로 만듬
                reduplication++;
                for (i = y; i < y + 3; i++) {
                    for (j = x; j < x + 3; j++) {
                        game_board[i][j] = 0;
                    }
                }
            }
        }
    }

    /* 다 찬 가로를 다시 0으로 만듬 */
    for (i = 0; i < 9; i++) {
        if (row[i] == true) {
            for (j = 0; j < 9; j++) {
                game_board[i][j] = 0;
            }
        }
    }

    /* 다 찬 세로를 다시 0으로 만듬 */
    for (j = 0; j < 9; j++) {
        if (col[j] == true) {
            for (i = 0; i < 9; i++) {
                game_board[i][j] = 0;
            }
        }
    }

    if (reduplication != 0) { // 점수 계산 후 더한다
        score += 18 + 10 * (reduplication - 1);
    }
}

/* 블록을 keep하면 해당 블록의 크기만큼 점수를 추가하는 함수 */
void plus_score(int &score, int (*block)[5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (block[i][j] == 1) {
                score++;
            }
        }
    }
}
