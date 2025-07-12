CC = gcc #-Wall -Werror -Wextra
CFLAGS = -std=c11 

SRC = brick_game/tetris/main.c brick_game/tetris/backend.c brick_game/fsm.c gui/cli/frontend.c
OBJ = brick_game/tetris/main.o brick_game/tetris/backend.o brick_game/fsm.o gui/cli/frontend.o

EXEC = tetris

all: clean $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lncurses  # Компиляция и линковка с ncurses
	./$(EXEC)

main.o: brick_game/tetris/main.c
	$(CC) $(CFLAGS) -c brick_game/tetris/main.c -o brick_game/tetris/main.o

backend.o: brick_game/tetris/backend.c
	$(CC) $(CFLAGS) -c brick_game/tetris/backend.c -o brick_game/tetris/backend.o

fsm.o: brick_game/fsm.c
	$(CC) $(CFLAGS) -c brick_game/fsm.c -o brick_game/fsm.o

frontend.o: gui/cli/frontend.c
	$(CC) $(CFLAGS) -c gui/cli/frontend.c -o gui/cli/frontend.o

clean:
	rm -f $(OBJ) $(EXEC)  # Удаляем объектные и исполнимые файлы
