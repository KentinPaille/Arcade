##
## EPITECH PROJECT, 2023
## Arcade
## File description:
## Makefile
##

#* Snake
SRCSNAKE = Snake/snake.cpp
OBJSNAKES = $(SRCSNAKE:.cpp=.o)
NAMESNAKES = arcade_snake.so

#* Nibbler
SRCSNIBBLER = Nibbler/nibbler.cpp
OBJSNIBBLER = $(SRCSNIBBLER:.cpp=.o)
NAMESNIBBLER = arcade_nibbler.so

%.o: %.cpp
	$(CC) -c -fPIC -o $@ $<

all: $(NAMESNAKES) $(NAMESNIBBLER)

$(NAMESNAKES): $(OBJSNAKES)
	$(CC) -shared -o $(NAMESNAKES) $(OBJSNAKES)
	mv $(NAMESNAKES) ../

$(NAMESNIBBLER): $(OBJSNIBBLER)
	$(CC) -shared -o $(NAMESNIBBLER) $(OBJSNIBBLER)
	mv $(NAMESNIBBLER) ../

clean:
	$(RM) $(OBJSNAKES) $(OBJSNIBBLER)

fclean: clean
	$(RM) ../$(NAMESNAKES) ../$(NAMESNIBBLER)

re: fclean all clean
