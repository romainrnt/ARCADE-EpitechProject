##
## EPITECH PROJECT, 2022
## B-OOP-400-STG-4-1-arcade-pierre.maurer
## File description:
## Makefile
##

all: core games graphicals

graphicals:
	make -C src/SFML
	make -C src/Ncurses
	make -C src/SDL2

games:
	cd src/Snake && make
	cd src/NibblerS && make

core:
	make -C src/Core
	make -C src/Menu

clean:
	cd src/Ncurses && make clean
	cd src/SFML && make clean
	cd src/Core && make clean
	cd src/Menu && make clean
	cd src/Snake && make clean
	cd src/SDL2 && make clean

fclean:
	cd src/Ncurses && make fclean
	cd src/SFML && make fclean
	cd src/Core && make fclean
	cd src/Menu && make fclean
	cd src/Snake && make fclean
	cd src/SDL2 && make fclean

re:	fclean all

.PHONY:	graphicals games core all clean fclean re