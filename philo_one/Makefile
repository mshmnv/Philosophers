.PHONY: all clean fclean re norme

NAME = philo_one

SRC = utils.c actions.c display.c error.c

HEADER = philo_one.h

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o:%.c
	@gcc $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) main.c
	gcc $(FLAGS) main.c $(OBJ) -o philo_one

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norme:
	@norminette $(SRC)