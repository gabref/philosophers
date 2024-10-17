CC = cc
FLAGS = -Wall -Wextra -Werror
# FLAGS = -Wall -Wextra -Werror -ggdb -fsanitize=thread
NAME = philo
SRC = main.c \
	  philo.c \
	  safe_functions.c \
	  utils.c \
	  dinner.c \
	  meals.c \
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

# setarch $(uname -m) -R ./philo 5 800 200 200
# The issue is caused by Address Space Layout Randomization (ASLR) interfering with ThreadSanitizer's shadow memory tracking. ASLR randomizes memory addresses, and TSan expects predictable memory ranges to monitor memory access. By using the setarch command with the -R flag, I disable ASLR, which allows TSan to function correctly. This workaround is necessary in environments where TSan's shadow memory conflicts with the system's memory layout.
