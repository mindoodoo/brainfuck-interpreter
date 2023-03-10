SRC = src/main.c
OBJ = $(SRC:.c=.o)

LDFLAGS = -Wall -Werror -std=c17

NAME = bf

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) myprog