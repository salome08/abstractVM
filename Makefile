NAME = abstractVm

CC = clang++ -std=c++11

FLAGS = -Wall -Wextra

SRC = main.cpp Exception.cpp Factory.cpp Operand.cpp 

OBJ = $(SRC:.cpp=.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

%.o:%.cpp
	$(CC) -c $^ $(FLAGS) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : re fclean clean all