#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../fsm.h"
#include "backend.h"

#define BOARD_N 20  // board height
#define BOARD_M 10  // board width
#define FIGURE_SIZE 4
#define HUD_WIDTH 8

void game_loop();

#endif