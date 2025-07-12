#include "main.h"
int main() {
  srand(time(NULL));  // Инициализация генератора случайных чисел
  initscr();
  cbreak();
  raw();
  curs_set(0);           // убираем мигающий курсор
  keypad(stdscr, TRUE);  // разрешаем стрелки
  timeout(500);
  noecho();
  nodelay(stdscr, TRUE);
  init_colors();  // убираем вводимый символ с начала
  game_loop();
  endwin();
  return 0;
}

void game_loop() {
  bool break_flag = TRUE;
  GameState state = START;
  // int start_y = 0;
  // int start_x = 4;
  // int figure[4][4] = {0};

  GameInfo_t gameInfo = updateCurrentState();
  // Block_t block = updateCurrentBlock();

  // gameInfo = updateCurrentState();
  // gameInfo.next = choosing_figure(gameInfo.next);  // ----
  while (break_flag) {
    // if (state == GAME_OVER || state == EXIT) break_flag = FALSE;
    // get_signal(signal);
    userInput(get_signal(), 1);
    gameInfo = updateCurrentState();
    refreshing_the_rendering(gameInfo);
    // sigact(&start_y, &start_x, figure, get_signal(signal), &state,
    // &gameInfo);

    // if (state == SPAWN || state == SHIFTING || state == MOVING ||
    //     state == START)
  }
}
