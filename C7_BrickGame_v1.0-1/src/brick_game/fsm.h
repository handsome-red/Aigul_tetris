#ifndef FSM_H
#define FSM_H

#include "../gui/cli/frontend.h"
#include "game_info.h"
#include "tetris/backend.h"
#include "tetris/main.h"

typedef enum {
  Start = 0,  // Enter
  Pause,      // P
  Terminate,  // Q
  Left,       // <-
  Right,      // ->
  Up,         // nothing
  Down,       // v
  Action,
  NoAction  // space
} UserAction_t;

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  CONNECT,
  GAME_OVER,
  EXIT,
  PAUSE
} GameState;

typedef struct {
  int start_x;
  int start_y;   // координаты фигуры
  int **figure;  // сделать динамику
} Block_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();
Block_t updateCurrentBlock();

UserAction_t get_signal();
void sigact(GameInfo_t *gameInfo);

void on_start_state(UserAction_t sig, GameInfo_t *gameInfo, GameState *state);
void on_spawn_state(int *start_y, int *start_x, int figure[4][4],
                    GameInfo_t *gameInfo, GameState *state);
void on_moving_state(int *start_y, int *start_x, int figure[4][4],
                     GameInfo_t *gameInfo, UserAction_t sig, GameState *state);
void on_shifting_state(int *start_y, int *start_x, int figure[4][4],
                       GameInfo_t *gameInfo, GameState *state);
void on_connect_state(int *start_y, int *start_x, int figure[4][4],
                      GameInfo_t *gameInfo, GameState *state);
void on_game_over_state(UserAction_t sig, GameState *state);
void on_exit_state();
void on_pause_state(UserAction_t sig, GameState *state, GameInfo_t *gameInfo);
GameInfo_t *get_game_info();

#endif