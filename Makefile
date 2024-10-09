CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ls.c long_form.c my_qsort.c my_scandir.c
OBJ = $(SRC:.c=.o)
NAME = ft_ls

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
