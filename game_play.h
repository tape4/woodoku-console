#include "Queue.h"
#include "block.h"

void get_block_min_max_i_j(int (*)[9], int &, int &, int &, int &);
void block_size_to_nine(int (*)[5], int (*)[9]);
bool move_left(int (*)[9]);
bool move_right(int (*)[9]);
bool move_up(int (*)[9]);
bool move_down(int (*)[9]);
void overlap_board_and_block(int (*)[9], int (*)[9], int (*)[9]);
