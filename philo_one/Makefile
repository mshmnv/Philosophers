.PHONY: all clean fclean re norme

NAME = philo_one

SRC = utils.c actions.c

HEADER = philo_one.h

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

%.o:%.c
	@gcc $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	gcc -g main.c $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norme:
	@norminette $(SRC)