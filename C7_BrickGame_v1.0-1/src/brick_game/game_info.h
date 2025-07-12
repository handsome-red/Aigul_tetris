#ifndef GAME_INFO_H
#define GAME_INFO_H
#define BOARD_N 20  // board height
#define BOARD_M 10  // board width
#define FIGURE_SIZE 4
#include "fsm.h"

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;
// // void userInput(UserAction_t action, bool hold);
// GameInfo_t updateCurrentState(GameInfo_t *gameInfo);
#endif