#include "backend.h"

void falling(int *start_y) { *start_y += 1; }

void shift_right(int *start_x, int **figure) {
  if (can_shift_right(start_x, figure)) *start_x += 1;
}
void shift_left(int *start_x, int **figure) {
  if (can_shift_left(start_x, figure)) *start_x -= 1;
}
void shift_down(int *start_y, int *start_x, int **figure,
                GameInfo_t *gameInfo) {
  if (can_fall(start_y, start_x, figure, gameInfo)) *start_y += 1;
}

int **choosing_figure(int **next) {
  int figures[7][4][4] = {
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},  // O-0
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},  // I-1
      {{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}},  // S-2
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},  // Z-3
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}},  // L-4
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}},  // J-5
      {{0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}},  // T-6
  };
  int rand_index = rand() % 7;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      next[i][j] = figures[rand_index][i][j];
    }
  return next;
}

void fall_figure(int *start_y, int *start_x, int **figure,
                 GameInfo_t *gameInfo) {
  while (can_fall(start_y, start_x, figure, gameInfo)) {
    *start_y += 1;
  }
}
int can_shift_right(int *start_x, int **figure) {
  int can_shift = 1;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (figure[i][j] == 1 && *start_x + j >= BOARD_M - 1) can_shift = 0;
    }
  return can_shift;
}

int can_shift_left(int *start_x, int **figure) {
  int can_shift = 1;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (figure[i][j] == 1 && (*start_x + j) <= 0) can_shift = 0;
    }
  return can_shift;
}

int can_fall(int *start_y, int *start_x, int **figure, GameInfo_t *gameInfo) {
  int flag = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure[i][j] == 1) {
        int new_y = *start_y + i + 1;
        int new_x = *start_x + j;
        if (new_y >= BOARD_N ||
            (new_y >= 0 && new_y < BOARD_N && new_x >= 0 && new_x < BOARD_M &&
             gameInfo->field[new_y][new_x] == 1)) {
          flag = 0;
        }
      }
    }
  }
  return flag;
}

void connect(int *start_y, int *start_x, int **figure, GameInfo_t *gameInfo) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure[i][j] == 1) {
        int new_y = *start_y + i;
        int new_x = *start_x + j;
        if (new_y >= 0 && new_y < BOARD_N && new_x >= 0 && new_x < BOARD_M) {
          gameInfo->field[new_y][new_x] = 1;
        }
      }
    }
  }
}

void turn_figure(int *start_y, int *start_x, int **figure,
                 GameInfo_t *gameInfo) {
  int new_figure[4][4] = {0};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      new_figure[j][3 - i] = figure[i][j];
    }
  if (can_shift_right(start_x, new_figure) &&
      can_shift_left(start_x, new_figure) &&
      can_fall(start_y, start_x, figure, gameInfo)) {
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++) {
        figure[i][j] = new_figure[i][j];
      }
  }
}

int board_overflow(GameInfo_t *gameInfo) {
  int flag = 0;
  for (int i = 0; i < 3; i++) {  // Проверяем первые 3 строки
    for (int j = 0; j < BOARD_M; j++) {
      if (gameInfo->field[i][j] == 1) {
        flag = 1;
        break;  // Прерываем внутренний цикл, если нашли занятую клетку
      }
    }
    if (flag == 1) {
      break;  // Прерываем внешний цикл, если нашли занятую клетку
    }
  }
  return flag;  // Если flag == 1, значит поле переполнено
}

int check_full_line(GameInfo_t *gameInfo, int row) {
  int flag = 1;
  for (int j = 0; j < BOARD_M; j++) {
    if (gameInfo->field[row][j] == 0) flag = 0;
  }
  return flag;
}

void remove_line(GameInfo_t *gameInfo, int row) {
  for (int i = row; i > 0; i--)
    for (int j = 0; j < BOARD_M; j++) {
      gameInfo->field[i][j] = gameInfo->field[i - 1][j];
    }
  for (int j = 0; j < BOARD_M; j++) {
    gameInfo->field[0][j] = 0;
  }
}

void processing_full_lines(GameInfo_t *gameInfo) {
  for (int i = 0; i < BOARD_N; i++) {
    if (check_full_line(gameInfo, i)) {
      remove_line(gameInfo, i);
      i--;
    }
  }
}

bool timer(int level, bool pause) {
  bool result = false;
  static struct timespec current_time = {0, 0};
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);

  int tick = 1000 / (1 + level * 0.5);
  if (tick < 50) {
    tick = 50;
  }

  double tick_check = (now.tv_sec - current_time.tv_sec) * 1000 +
                      (now.tv_nsec - current_time.tv_nsec) / 1000000;

  if (tick <= tick_check && pause == 0) {
    result = false;
    current_time = now;
  }
  return result;
}

int **create_matrix(int n, int m) {
  int **matrix = (int **)calloc(n, sizeof(int *));
  if (matrix == NULL) {
    return NULL;
  }
  for (int i = 0; i < n; i++) {
    (matrix)[i] = (int *)calloc(m, sizeof(int));
    if ((matrix)[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free((matrix)[j]);
      }
      free(matrix);
      matrix = NULL;
      return NULL;
    }
  }
  return matrix;
}

void free_matrix(int n, int ***matrix) {
  if (matrix) {
    for (int i = 0; i < n; i++) {
      if (matrix[i]) free(matrix[i]);
    }
    if (matrix) free(matrix);
    matrix = NULL;
    n = 0;
  }
}

void safe_record(int score) {
  FILE *file = fopen("../../best_score.txt", "rw+");
  int record = 0;
  fscanf(file, "%d", &record);
  if (record < score) {
    rewind(file);
    fprintf(file, "%d", score);
  }
  fclose(file);
}

void attach_figure_in_field(GameInfo_t *gameInfo) {
  Block_t block = updateCurrentBlock();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (block.figure[i][j] == 1) {
        int new_y = block.start_y + i;
        int new_x = block.start_x + j;
        if (new_y >= 0 && new_y < BOARD_N && new_x >= 0 && new_x < BOARD_M) {
          gameInfo->field[new_y][new_x] = 2;
        }
      }
    }
  }
}

void detach_figure_in_field(GameInfo_t *gameInfo) {
  for (int i = 0; i < BOARD_N; i++) {
    for (int j = 0; j < BOARD_M; j++) {
      if (gameInfo->field[i][j] == 2) {
        gameInfo->field[i][j] = 0;
      }
    }
  }
}
