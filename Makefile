##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

NAME	=	arcade

SRC		=	src/main.cpp \
			src/core.cpp \
			src/menu.cpp \

OBJ		=	$(SRC:.cpp=.o)

CC		=	g++

CFLAGS	=	-I./includes

ERRORFLAGS	=	-std=c++20 -Wall -Wextra -Werror

all:	core graphicals games

core:	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(ERRORFLAGS)
		make clean

graphicals:
		make -C lib/display/

games:
		make -C lib/games/

bonus:
		make -C bonus/

clean:
	$(RM) $(OBJ)
	make clean -C lib/display/
	make clean -C lib/games/
	make clean -C bonus/

fclean: clean
	$(RM) $(NAME) unit_tests $(OBJ)
	make fclean -C lib/display/
	make fclean -C lib/games/
	make fclean -C bonus/

re:	fclean all

.PHONY:	 clean fclean re all core graphicals games bonus
