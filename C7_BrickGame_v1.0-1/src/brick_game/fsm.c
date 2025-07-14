#include "fsm.h"

UserAction_t get_signal() {
  int user_input = getch();
  UserAction_t rc = -1;

  // UserAction_t rc = Up;

  if (user_input == KEY_UP)
    rc = Up;
  else if (user_input == KEY_DOWN)
    rc = Down;
  else if (user_input == KEY_LEFT)
    rc = Left;
  else if (user_input == KEY_RIGHT)
    rc = Right;
  else if (user_input == 'q')
    rc = Terminate;
  else if (user_input == 's')
    rc = Start;
  else if (user_input == ' ')
    rc = Action;
  else if (user_input == 'p')
    rc = Pause;
  return rc;
}

GameState sigact(GameInfo_t *gameInfo, GameState state,
                 Block_t *block) {  // FSM machine
  // state = update_state_machine(NO_STATE);
  // Block_t block = updateCurrentBlock(); // Поменялся

  switch (state) {
    case START:

      // prepare_figure_next();
      // state = SPAWN;
      // on_start_state(gameInfo, &state);
      on_start_state(gameInfo);
      // state = update_state_machine(SPAWN);
      state = SPAWN;
      break;
    case SPAWN:
      on_spawn_state(&block->start_y, &block->start_x, block->figure, gameInfo,
                     &state);
      break;
    case SHIFTING:
      on_shifting_state(&block->start_y, &block->start_x, block->figure,
                        gameInfo, &state);
      break;
    case MOVING:
      // on_moving_state(block.start_y, block.start_x, block.figure, gameInfo,
      // sig,
      //                 &state);
      break;
    case CONNECT:
      on_connect_state(&block->start_y, &block->start_x, block->figure,
                       gameInfo, &state);
      break;
    case GAME_OVER:
      // on_game_over_state(sig, &state);
      break;
    // case PAUSE:
    //   // on_pause_state(sig, &state, gameInfo);
    //   break;
    // case EXIT:
    //   on_exit_state(&state);
    //   break;
    default:
      break;
  }
  return state;
}

void on_start_state(GameInfo_t *gameInfo) {
  UserAction_t sig = Start;
  gameInfo->next = choosing_figure(gameInfo->next);
  // switch (sig) {
  //   case Start:
  //     *state = SPAWN;
  //     break;
  //   default:
  //     *state = START;
  //     break;
  // }
}

void on_spawn_state(int *start_y, int *start_x, int **figure,
                    GameInfo_t *gameInfo, GameState *state) {
  *start_y = 0;
  *start_x = 4;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      figure[i][j] = gameInfo->next[i][j];
    }
  gameInfo->next = choosing_figure(gameInfo->next);
  *state = SHIFTING;
}

void on_shifting_state(int *start_y, int *start_x, int **figure,
                       GameInfo_t *gameInfo, GameState *state) {
  (*start_y) += 1;

  if (!can_fall(start_y, start_x, figure, gameInfo)) *state = CONNECT;
  // else
  //   *state = MOVING;
}

void on_moving_state(int *start_y, int *start_x, int **figure,
                     GameInfo_t *gameInfo, UserAction_t sig, GameState *state) {
  switch (sig) {
    case Up:
      turn_figure(start_y, start_x, figure, gameInfo);
      break;
    case Down:
      shift_down(start_y, start_x, figure, gameInfo);
      break;
    case Right:
      shift_right(start_x, figure);
      break;
    case Left:
      shift_left(start_x, figure);
      break;
    case Action:
      fall_figure(start_y, start_x, figure, gameInfo);
      break;
    case Pause:
      gameInfo->pause = 1;
      *state = PAUSE;
      break;
    case Terminate:
      *state = EXIT;
      break;
    default:
      break;
  }
  if (*state != EXIT) {
    if (!can_fall(start_y, start_x, figure, gameInfo))
      *state = CONNECT;
    else
      *state = SHIFTING;
  }
}

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *gameInfo = get_game_info();  // 2 variant
  Block_t *block = get_block();            // 2 variant
  // GameState state = update_state_machine(NO_STATE);

  switch (action) {
    case Start:
      update_state_machine(SPAWN);
      // Подготовить фигуру next
      // Перейти в состояние SPAWN при нажатии enter
      break;
    case Pause:
      gameInfo->pause = !gameInfo->pause;
      break;
    case Terminate:
      // safe_record(gameInfo->score);
      free_matrix(BOARD_N, gameInfo->field);
      free_matrix(FIGURE_SIZE, gameInfo->next);
      free_matrix(FIGURE_SIZE, block->figure);  // возможно утечка
      endwin();
      exit(0);
      break;
    case Left:
      gameInfo->score = block->start_x;
      shift_left(&block->start_x, block->figure);
      break;
    case Right:
      shift_right(&block->start_x, block->figure);
      break;
      // case Up:
      //   turn_figure(&block->start_y, &block->start_x, block->figure,
      //   gameInfo); break;
      // case Down:
      //   shift_down(&block->start_y, &block->start_x, block->figure,
      //   gameInfo); break;
      // case Action:
      //   fall_figure(&block->start_y, &block->start_x, block->figure,
      //   gameInfo); break;
      // default:
      //   break;
  }
}
// 1 START - enter = запускать игру

void on_connect_state(int *start_y, int *start_x, int **figure,
                      GameInfo_t *gameInfo, GameState *state) {
  connect(start_y, start_x, figure, gameInfo);
  processing_full_lines(gameInfo);
  if (board_overflow(gameInfo))
    *state = GAME_OVER;
  else {
    *state = SPAWN;
  }
}

void on_game_over_state(UserAction_t sig, GameState *state) {
  while (1) {
    sig = get_signal(getch());
    print_game_over_banner();
    if (sig == Terminate) {
      *state = EXIT;
      break;
    } else if (sig == Start) {
      *state = START;
      break;
    }
  }
}
void on_exit_state() {
  endwin();
  exit(0);
}

void on_pause_state(UserAction_t sig, GameState *state, GameInfo_t *gameInfo) {
  while (gameInfo->pause) {
    sig = get_signal(getch());
    if (sig == Start) {
      *state = MOVING;
      gameInfo->pause = 0;
      break;
    } else if (sig == Terminate) {
      *state = EXIT;
      gameInfo->pause = 0;
      break;
    }
  }
}

GameInfo_t updateCurrentState() {
  GameInfo_t gameInfo = *get_game_info();
  return gameInfo;
}

GameInfo_t *get_game_info() {
  static GameInfo_t *gameInfo = NULL;
  Block_t *block = get_block();

  static int signal = 0;
  static GameState state = START;

  if (NULL == gameInfo) {
    gameInfo = calloc(1, sizeof(GameInfo_t));
    gameInfo->field = create_matrix(BOARD_N, BOARD_M);
    gameInfo->next = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
    gameInfo->speed = 100;
  } else if (timer(gameInfo->level, gameInfo->pause)) {
    detach_figure_in_field(gameInfo);
    state = sigact(gameInfo, state, block);
    attach_figure_in_field(gameInfo, *block);
  }

  return gameInfo;
}

Block_t updateCurrentBlock() {
  Block_t block = *get_block();
  return block;
}

Block_t *get_block() {
  static Block_t *block = NULL;

  if (NULL == block) {
    block = calloc(1, sizeof(GameInfo_t));
    block->figure = create_matrix(FIGURE_SIZE, FIGURE_SIZE);
    block->start_x = 4;
  }

  return block;
}

// block.c (или в том же файле, где updateCurrentBlock)

// передали spawn получили spawn
GameState update_state_machine(GameState state) {
  static GameState new_state = START;
  if (state != NO_STATE) {
    new_state = state;
  }
  return new_state;
}

// if (gameInfo->score > gameInfo->high_score) {
//   gameInfo->high_score = gameInfo->score;
// }
// if (gameInfo->score >= 100) {
//   gameInfo->level = 2;
//   gameInfo->speed = 800;
// } else if (gameInfo->score >= 200) {
//   gameInfo->level = 3;
//   gameInfo->speed = 600;
// }
// if (gameInfo->pause == 1) {
//   print_pause_banner();
// }
