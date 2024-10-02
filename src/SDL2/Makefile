##
## EPITECH PROJECT, 2022
## B-OOP-400-STG-4-1-arcade-pierre.maurer
## File description:
## Makefile
##

SRC		=	./Sdl.cpp	\
			../Tools/Text/Text.cpp			\
			../Tools/Pixel/Pixel.cpp		\

OBJ		=	$(SRC:.cpp=.o)

NAME	=	arcade_sdl2.so

all:	$(NAME)

CFLAGS	=		-shared -Wall -Wextra -fPIC -I../../include/

LFLAGS  =		-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -ldl

$(NAME):	$(OBJ)
	g++ $(CFLAGS) $(SRC) -o $(NAME) $(LFLAGS)
	mv $(NAME) ../../lib

clean:
	rm -f $(OBJ)
	rm -f *.o

fclean:	clean
	rm -f ../../lib/$(NAME)

re:	fclean all