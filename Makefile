##
## EPITECH PROJECT, 2019
## Makefile
## File description:
##
##

NAME =	groundhog

SRC =	src/main.cpp \
		src/Groundhog.cpp

OBJ =	$(SRC:.cpp=.o)

CC =	g++

CFLAGS =	-W -Wall -Wextra -g3

RM =	rm -f

RULE =	all

all :	$(NAME)

$(NAME) :	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -g3

clean :
		$(RM) $(OBJ)

fclean :	clean
			$(RM) $(NAME)

re :	fclean all
