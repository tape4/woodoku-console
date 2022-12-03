#pragma once
#include <cstring> // for memset, strcat
#include <fcntl.h>
#include <iostream>
#include <ncurses.h>
#include <queue>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void get_ranking();
void init_priority_queue();
void append_ranking(char *, int);
