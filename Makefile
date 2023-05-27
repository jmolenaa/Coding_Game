CFLAGS = -Wall -Werror -Wextra
CC = cc
INCLUDES = -I incs
NAME = coding_game
OBJ=main.o


all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
