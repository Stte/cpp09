NAME := PmergeMe
CC := c++
FLAGS := -Wall -Wextra -Werror -std=c++11
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Executable: ./$(NAME)"
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ)

$(OBJ): $(SRC)
	@$(CC) -c $(FLAGS) $(SRC)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
