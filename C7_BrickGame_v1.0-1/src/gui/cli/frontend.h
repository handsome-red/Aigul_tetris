#ifndef FRONTEND_H
#define FRONTEND_H
#include <ncurses.h>

#include "../../brick_game/fsm.h"
#include "../../brick_game/game_info.h"
#include "../../brick_game/tetris/main.h"

#define BOARD_N 20  // board height
#define BOARD_M 10  // board width
#define HUD_WIDTH 8
#define BLOCK 32 | A_REVERSE
void init_colors();
void print_game_board(int **field);
void print_board();
void print_next_figure(int **next);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_start_banner();
void print_game_over_banner();
void print_pause_banner();
void print_hud(GameInfo_t gameInfo);
void print_figure(int *start_y, int *start_x, int figure[4][4]);
void refreshing_the_rendering(GameInfo_t gameInfo);
#endif