#include "block.h"

/* 9*9 블록의 i, j 최소, 최대값을 구한다 */
void get_block_min_max_i_j(int (*block)[9], int &min_i, int &min_j, int &max_i,
                           int &max_j) {
    min_i = 8;
    min_j = 8;
    max_i = 0;
    max_j = 0;

    /* 9x9 블록의 i, j 최소, 최대값을 구한다 */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (block[i][j] == 1) {
                if (min_i > i)
                    min_i = i;
                if (min_j > j)
                    min_j = j;
                if (max_i < i)
                    max_i = i;
                if (max_j < j)
                    max_j = j;
            }
        }
    }
}

/* 5x5 블록을 9x9 블록의 가장 왼쪽 위에 위치하도록 변환 */
void block_size_to_nine(int (*block)[5], int (*size_nine_block)[9]) {
    /* 처음에 사이즈가 9인 블록을 0으로 초기화 */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            size_nine_block[i][j] = 0;
        }
    }

    int min_i = 4;
    int min_j = 4;
    int max_i = 0;
    int max_j = 0;

    /* 5x5 블록의 i, j 최소, 최대값을 구한다 */
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (block[i][j] == 1) {
                if (min_i > i) {
                    min_i = i;
                }
                if (min_j > j) {
                    min_j = j;
                }
                if (max_i < i) {
                    max_i = i;
                }
                if (max_j < j) {
                    max_j = j;
                }
            }
        }
    }

    /* 5x5 블록을 9x9 블록의 가장 왼쪽 위에 놓이도록 구현한다 */
    for (int i = min_i; i <= max_i; i++) {
        for (int j = min_j; j <= max_j; j++) {
            if (block[i][j] == 1) {
                size_nine_block[i - min_i][j - min_j] = 1;
            }
        }
    }
}

/* 9x9 블록을 받아 왼쪽으로 한칸 움직인다 */
void move_left(int (*block)[9]) {
    int min_i, min_j, max_i, max_j;
    get_block_min_max_i_j(block, min_i, min_j, max_i, max_j);

    if (min_j == 0) { // 더이상 왼쪽으로 블록 이동 불가능
        return;
    }

    int new_block[9][9] = {
        // 왼쪽으로 한칸 움직인 블록을 저장
        0,
    };

    /* block에서 왼쪽으로 한칸 움직인 상태를 new_block에 저장 */
    for (int i = 8; i > 0; i--) {
        for (int j = 8; j > 0; j--) {
            if (block[i][j] == 1) {
                new_block[i][j - 1] = 1;
            }
        }
    }

    /* block 업데이트 */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            block[i][j] = new_block[i][j];
        }
    }
}

/* 9x9 블록을 받아 오른쪽으로 한칸 움직인다 */
void move_right(int (*block)[9]) {
    int min_i, min_j, max_i, max_j;
    get_block_min_max_i_j(block, min_i, min_j, max_i, max_j);

    if (max_j == 8) { // 더이상 오른쪽으로 블록 이동 불가능
        return;
    }

    int new_block[9][9] = {
        // 오른쪽으로 한칸 움직인 블록을 저장
        0,
    };

    /* block에서 오른쪽으로 한칸 움직인 상태를 new_block에 저장 */
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (block[i][j] == 1) {
                new_block[i][j + 1] = 1;
            }
        }
    }

    /* block 업데이트 */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            block[i][j] = new_block[i][j];
        }
    }
}

/* 9x9 블록을 받아 위로 한칸 움직인다 */
void move_up(int (*block)[9]) {
    int min_i, min_j, max_i, max_j;
    get_block_min_max_i_j(block, min_i, min_j, max_i, max_j);

    if (min_i == 0) { // 더이상 위로 블록 이동 불가능
        return;
    }

    int new_block[9][9] = {
        // 위로 한칸 움직인 블록을 저장
        0,
    };

    /* block에서 위로 한칸 움직인 상태를 new_block에 저장 */
    for (int i = 8; i > 0; i--) {
        for (int j = 8; j > 0; j--) {
            if (block[i][j] == 1) {
                new_block[i - 1][j] = 1;
            }
        }
    }

    /* block 업데이트 */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            block[i][j] = new_block[i][j];
        }
    }
}

/* 9x9 블록을 받아 아래로 한칸 움직인다 */
void move_down(int (*block)[9]) {
    int min_i, min_j, max_i, max_j;
    get_block_min_max_i_j(block, min_i, min_j, max_i, max_j);

    if (max_i == 8) { // 더이상 아래로 블록 이동 불가능
        return;
    }

    int new_block[9][9] = {
        // 아래로 한칸 움직인 블록을 저장
        0,
    };

    /* block에서 아래로 한칸 움직인 상태를 new_block에 저장 */
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (block[i][j] == 1) {
                new_block[i + 1][j] = 1;
            }
        }
    }

    /* block 업데이트 */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            block[i][j] = new_block[i][j];
        }
    }
}
