/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** menu
*/

#include "../includes/core.hpp"

void menu_event(ac::Core *core)
{
    core->_event = core->_currentDisplay->event();
    if (core->_event == ac::Core::Input::Key::UP) {
        if (core->_selectMenu == core->getNumberOfGameLibs())
            core->_userNameWrite = core->getUserName();
        if (core->_selectMenu - 1 >= 0)
            core->_selectMenu -= 1;
    }
    if (core->_event == ac::Core::Input::Key::DOWN) {
        if (core->_selectMenu + 1 <= core->getNumberOfGameLibs())
            core->_selectMenu += 1;
    }
    if (core->_event == ac::Core::Input::Key::RIGHT) {
        core->_currentDisplay->end();
        core->changeLibrary(1);
    }
    if (core->_event == ac::Core::Input::Key::LEFT) {
        core->_currentDisplay->end();
        core->changeLibrary(-1);
    }
    if (core->_event == ac::Core::Input::Key::ENTER) {
        if (core->_selectMenu == core->getNumberOfGameLibs()) {
            core->setUserName(core->_userNameWrite);
        } else {
            core->_game = core->_selectMenu + 1;
            core->_score = 0;
            core->loadGame();
        }
    }
    if (core->_event == ac::Core::Input::Key::ESCAPE) {
        core->_isRunning = false;
    }
    if (core->_event == ac::Core::Input::Key::BACKSPACE) {
        core->fillUserName(-1);
    }
    else {
        if ((core->_event >= 'a' && core->_event <= 'z'
         || core->_event >= 'A' && core->_event <= 'Z'
         || core->_event >= '0' && core->_event <= '9'
         || core->_event == ' ' || core->_event == '_')
         && core->_selectMenu == core->getNumberOfGameLibs())
            core->fillUserName(core->_event);
    }
}

void menu(ac::Core *core)
{
    int offsetY = 7;
    int nbGameLibs = core->getNumberOfGameLibs();

    core->_currentDisplay->printLogo();

    for (int i = 0; i < nbGameLibs; i++) {
        if (i == core->_selectMenu)
            core->_currentDisplay->printText(">", 12, offsetY + i);
        core->_currentDisplay->printText(core->getGameList()[i].name.c_str(), 14, offsetY + i);
    }
    if (core->_selectMenu == nbGameLibs) {
        core->_currentDisplay->printText("> Enter your name:", 10, offsetY + nbGameLibs + 1);
        core->_currentDisplay->printText(core->_userNameWrite.c_str(), 14, offsetY + nbGameLibs + 2);
    } else {
        core->_currentDisplay->printText("Enter your name: ", 12, offsetY + nbGameLibs + 1);
        core->_currentDisplay->printText(core->getUserName().c_str(), 14, offsetY + nbGameLibs + 2);
    }
    core->_currentDisplay->printText("Press LEFT to change library", 10, offsetY + nbGameLibs + 4);
    core->_currentDisplay->printText("Press RIGHT to change library", 10, offsetY + nbGameLibs + 5);
    core->_currentDisplay->printText("SCORE: " + std::to_string(core->_score), 10, offsetY + nbGameLibs + 7);
    core->printHighScores(offsetY);
    menu_event(core);
}
