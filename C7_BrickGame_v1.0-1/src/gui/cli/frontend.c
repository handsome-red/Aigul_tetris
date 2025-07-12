#include "frontend.h"
void print_board() {
  // Основной прямоугольник игрового поля
  print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 1);

  // // Прямоугольник для HUD
  // print_rectangle(0, BOARD_N + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 3);

  // // Прямоугольники для статистики
  // for (int i = 0; i < 3; i++) {
  //   print_rectangle(2 + i * 4, 4 + i * 4, BOARD_M + 3, BOARD_M + HUD_WIDTH +
  //   2);
  // }
  // print_rectangle(14, 17, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
}
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  // Верхняя граница
  mvaddch(top_y, left_x, ACS_ULCORNER);
  for (int i = left_x + 1; i < right_x * 2; i++) {
    mvaddch(top_y, i, ACS_HLINE);
  }
  mvaddch(top_y, right_x * 2, ACS_URCORNER);

  // Боковые границы
  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x * 2, ACS_VLINE);
  }

  // Нижняя граница
  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  for (int i = left_x + 1; i < right_x * 2; i++)
    mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(bottom_y, right_x * 2, ACS_LRCORNER);
}  ///////////////

// DONE
void print_game_board(int **field) {
  for (int i = 0; i < BOARD_N; i++) {
    for (int j = 0; j < BOARD_M; j++) {
      if (field[i][j] == 1) {
        // mvaddch(i + 1, j + 1, BLOCK);  // Айгуль
        mvaddch(i + 1, j * 2, BLOCK);      // Андрей
        mvaddch(i + 1, j * 2 + 1, BLOCK);  // Андрей
      }
    }
  }
}

// DONE
void print_next_figure(int **next) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (next[i][j] == 1) {
        mvaddch(i + 14, BOARD_M + 5 + j * 2, BLOCK);
        mvaddch(i + 14, BOARD_M + 5 + j * 2 + 1, BLOCK);
      }
    }
}

// DONE
void print_figure(int *start_y, int *start_x, int figure[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (figure[i][j] == 1) {
        mvaddch(*start_y + i, (*start_x + j) * 2, BLOCK);
        mvaddch(*start_y + i, (*start_x + j) * 2 + 1, BLOCK);
      }
    }
}

// void refreshing_the_rendering(int *start_y, int *start_x, int figure[4][4],
//                               GameInfo_t *gameInfo) {
//   clear();
//   print_board();
//   print_hud(gameInfo);
//   attron(COLOR_PAIR(1));
//   print_game_board(gameInfo);
//   print_figure(start_y, start_x, figure);
//   // print_next_figure(gameInfo->next); RETURN
//   attroff(COLOR_PAIR(1));
//   refresh();
// }

void refreshing_the_rendering(GameInfo_t gameInfo) {
  clear();
  print_board();
  print_hud(gameInfo);
  attron(COLOR_PAIR(1));
  print_game_board(gameInfo.field);
  // print_next_figure(gameInfo.next);
  attroff(COLOR_PAIR(1));
  refresh();
}

void init_colors() {
  if (has_colors()) {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
  }
}
void print_hud(GameInfo_t gameInfo) {
  mvprintw(1, (BOARD_M + 3) * 2, "Score:");
  mvprintw(3, (BOARD_M + 5) * 2, "%d", gameInfo.score);
  mvprintw(5, (BOARD_M + 3) * 2, "Level:");
  mvprintw(7, (BOARD_M + 5) * 2, "%d", gameInfo.level);
  mvprintw(9, (BOARD_M + 3) * 2, "Record:");
  mvprintw(11, (BOARD_M + 5) * 2, "%d", gameInfo.high_score);
  mvprintw(13, (BOARD_M + 3) * 2, "Next:");
}
void print_start_banner() {
  clear();
  print_rectangle(0, BOARD_N + 1, 0, BOARD_M + HUD_WIDTH + 3);
  mvprintw(9, 6, "Press Enter");
  mvprintw(11, 2, "to start the game!");
}
void print_game_over_banner() {
  clear();
  print_rectangle(0, BOARD_N + 1, 0, BOARD_M + HUD_WIDTH + 3);
  mvprintw(8, 6, "Game over!");
  mvprintw(10, 4, "Enter - return");
  mvprintw(12, 5, "to the start");
  mvprintw(14, 6, "Q - exit");
}
void print_pause_banner() {
  print_board();
  mvprintw(9, 6, "Pause");
  mvprintw(11, 3, "Press enter to return to the game");
}