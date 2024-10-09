CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ls.c long_form.c my_qsort.c my_scandir.c
NAME = ls

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
