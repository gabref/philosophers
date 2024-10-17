CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb -fsanitize=thread
NAME = philo
SRC = main.c \
	  philo.c \
	  safe_functions.c \
	  utils.c \
	  dinner.c \
	  init.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(FLAGS) -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
