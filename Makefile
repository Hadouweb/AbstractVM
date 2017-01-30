CC = clang++
CFLAGS = -Werror -Wall -Wextra -std=c++11 -g

NAME = abstractVM

SRC_PATH = ./srcs
INCLUDES = -I ./headers -I ./SFML/include


SRC =   $(SRC_PATH)/main.cpp\
        $(SRC_PATH)/Lexer.class.cpp\
        $(SRC_PATH)/Node.class.cpp\

OBJ = $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re