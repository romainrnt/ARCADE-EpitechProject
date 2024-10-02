##
## EPITECH PROJECT, 2022
## B-OOP-400-STG-4-1-arcade-pierre.maurer
## File description:
## Makefile
##

SRC		=	Core.cpp								\
			../../main.cpp							\
			../Tools/Loader/Loader.cpp				\
			../Tools/Text/Text.cpp					\
			../Tools/Pixel/Pixel.cpp				\
			../Tools/Errors/Exceptions.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	arcade

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -std=c++20 -g -o $(NAME) -Wall -Wextra -Werror $(OBJ) -ldl
	mv $(NAME) ../../

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../../$(NAME)

re:	fclean all