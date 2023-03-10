CC = gcc

SRC = src/main.c

CFLAGS = -Wall -Werror -std=c17 -Os -fomit-frame-pointer

NAME = bf

$(NAME):
	$(CC) $(SRC) -o $(NAME) $(CFLAGS) -I./include

clean:
	rm -f $(OBJ) bf

re: clean $(NAME)

.PHONY: clean