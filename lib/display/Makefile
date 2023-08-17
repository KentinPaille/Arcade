##
## EPITECH PROJECT, 2022
## arcade
## File description:
## Makefile
##

#* Ncurses
SRCNCURSE = Ncurses/ncurses.cpp
OBJNCURSES = $(SRCNCURSE:.cpp=.o)
NAMENCURSES = arcade_ncurses.so

#* SDL2
SRCSDL = Sdl2/sdl2.cpp
OBJSDL = $(SRCSDL:.cpp=.o)
NAMESDL = arcade_sdl2.so

#* Sfml
SRCSFML = Sfml/sfml.cpp
OBJSFML = $(SRCSFML:.cpp=.o)
NAMESFML = arcade_sfml.so

%.o: %.cpp
	$(CC) -c -fPIC -o $@ $<

all: $(NAMENCURSES) $(NAMESDL) $(NAMESFML)

$(NAMENCURSES): $(OBJNCURSES)
	$(CC) -shared -o $(NAMENCURSES) $(OBJNCURSES) -lncurses
	mv $(NAMENCURSES) ../

$(NAMESDL): $(OBJSDL)
	$(CC) -shared -o $(NAMESDL) $(OBJSDL) -lSDL2 -lSDL2_ttf
	mv $(NAMESDL) ../


$(NAMESFML): $(OBJSFML)
	$(CC) -shared -o $(NAMESFML) $(OBJSFML) -lsfml-graphics -lsfml-window -lsfml-system
	make clean
	mv $(NAMESFML) ../

clean:
	$(RM) $(OBJNCURSES) $(OBJSDL) $(OBJSFML)

fclean: clean
	$(RM) ../$(NAMENCURSES) ../$(NAMESDL) ../$(NAMESFML)

re: fclean all
