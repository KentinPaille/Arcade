##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

#* Raylib
SRCRAYLIB = Raylib/raylib.cpp
OBJRAYLIB = $(SRCRAYLIB:.cpp=.o)
NAMERAYLIB = arcade_raylib.so

CC		=	g++
CFLAGS	=	-I./includes

%.o: %.cpp
	$(CC) -c -fPIC -o $@ $<

all: $(NAMERAYLIB)

$(NAMERAYLIB): $(OBJRAYLIB)
	$(CC) -shared -o $(NAMERAYLIB) $(OBJRAYLIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -fPIC
	mv $(NAMERAYLIB) ../lib/

clean:
	$(RM) $(OBJRAYLIB)

fclean: clean
	$(RM) ../lib/$(NAMERAYLIB)

re: fclean all
