##
## EPITECH PROJECT, 2022
## B-OOP-400-STG-4-1-arcade-pierre.maurer
## File description:
## Makefile
##

SRC		=	Sfml.cpp						\
			../Tools/Text/Text.cpp			\
			../Tools/Pixel/Pixel.cpp		\

OBJ		=	$(SRC:.cpp=.o)

NAME	=	arcade_sfml.so

all:	$(NAME)

CFLAGS	=		-shared -Wall -Werror -Wextra -fPIC -I../../include/

LFLAGS  =		-std=c++20 -lsfml-graphics -lsfml-window -lsfml-system

$(NAME):	$(OBJ)
	g++ $(CFLAGS) $(SRC) -o $(NAME) $(LFLAGS)
	mv $(NAME) ../../lib

clean:
	rm -f $(OBJ)
	rm -f *.o

fclean:	clean
	rm -f ../../lib/$(NAME)

re:	fclean all