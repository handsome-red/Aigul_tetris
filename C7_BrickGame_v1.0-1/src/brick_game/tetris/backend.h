#ifndef BACKEND_H
#define BACKEND_H

#include "../fsm.h"
#include "../game_info.h"
#include "main.h"
#define BOARD_N 20  // board height
#define BOARD_M 10  // board width
#define FIGURE_SIZE 4
#define HUD_WIDTH 8
// function
int **choosing_figure(int **next);
int can_shift_right(int *start_x, int **figure);
int can_shift_left(int *start_x, int **figure);
int can_fall(int *start_y, int *start_x, int **figure, GameInfo_t *gameInfo);
int board_overflow(GameInfo_t *gameInfo);
int check_full_line(GameInfo_t *gameInfo, int row);
void remove_line(GameInfo_t *gameInfo, int row);
void processing_full_lines(GameInfo_t *gameInfo);

bool timer(int level, bool pause);
int **create_matrix(int n, int m);
void free_matrix(int n, int ***matrix);

void safe_record(int score);

// state function
void falling(int *start_y);
void shift_right(int *start_x, int **figure);
void shift_left(int *start_x, int **figure);
void turn_figure(int *start_y, int *start_x, int **figure,
                 GameInfo_t *gameInfo);
void shift_down(int *start_y, int *start_x, int **figure, GameInfo_t *gameInfo);
void fall_figure(int *start_y, int *start_x, int **figure,
                 GameInfo_t *gameInfo);
void connect(int *start_y, int *start_x, int **figure, GameInfo_t *gameInfo);
#endif