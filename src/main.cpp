/*
** EPITECH PROJECT, 2022
** Core
** File description:
** main.cpp
*/

#include "../includes/core.hpp"
#include <sys/time.h>
#include <unistd.h>

void menu(ac::Core *Core);

void usage(int ac)
{
    if (ac != 2) {
        std::cout << "Usage: ./arcade [lib]" << std::endl;
        exit (84);
    }
}

int moveLib(ac::Core *core)
{
    if (core->_event == ac::Core::Input::ESCAPE) {
        core->_game = 0;
        return 84;
    }
    if (core->_event == ac::Core::Input::Key::LEFT) {
        core->_currentDisplay->end();
        core->changeLibrary(-1);
    }
    if (core->_event == ac::Core::Input::Key::RIGHT) {
        core->_currentDisplay->end();
        core->changeLibrary(1);
    }
    return 0;
}

int main (int ac, char **av)
{
    usage(ac);
    try {
        char * libraryName = av[1];
        ac::Core core(libraryName);
        while (core._isRunning)
        {
            core._currentDisplay->displayClear();
            if (core._game == 0)
                menu(&core);
            else {
                if (moveLib(&core) == 84)
                    continue;
                if (core._currentGame->gameCompute(&core) == 1) {
                    core.saveScore();
                    core._game = 0;
                    continue;
                }
                core._currentDisplay->draw(core._currentGame->gameGetMap(), core._score);
                core._event = core._currentDisplay->event();
            }
            core._currentDisplay->displayRefresh();
        }
        core._currentDisplay->end();
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}

