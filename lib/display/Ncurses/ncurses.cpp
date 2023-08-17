/*
** EPITECH PROJECT, 2022
** Core
** File description:
** arcade_ncurse.cpp
*/

#include <iostream>

#include "ncurses.hpp"
#include <unistd.h>

#define White 1
#define Green 2
#define Red 3
#define Yellow 4
#define Black 5

static const char *LOGO_PATH = "./assets/logo/arcadeNcurse.txt";

extern "C" Ncurse *displayEntryPoint() {
    return new Ncurse;
}

Ncurse::Ncurse() {
    try {
        initscr();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
        if (has_colors() == FALSE) {
            endwin();
            throw NcurseException("Your terminal does not support color");
        }
        start_color();
        init_pair(White, COLOR_WHITE, COLOR_WHITE);
        init_pair(Green, COLOR_GREEN, COLOR_GREEN);
        init_pair(Red, COLOR_RED, COLOR_RED);
        init_pair(Yellow, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(Black, COLOR_BLACK, COLOR_BLACK);

        std::ifstream file(LOGO_PATH);
        if (!file.is_open())
            throw NcurseException("Can't open logo file");
        std::string line;
        while (std::getline(file, line))
            _logo.push_back(line);
        file.close();

    } catch (NcurseException &e) {
        std::cerr << e.what() << std::endl;
        Ncurse::~Ncurse();
        exit (84);
    }
}

Ncurse::~Ncurse() {
    if (_logo.size() > 0)
        _logo.clear();
    if (stdscr)
        endwin();
}

void Ncurse::end() {
    clear();
    keypad(stdscr, FALSE);
    curs_set(1);
    refresh();
    endwin();
}

void Ncurse::draw(std::vector<std::string> map, int score) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '#') {
                attron(COLOR_PAIR(White));
                mvprintw(i, j * 2, "  ");
                attroff(COLOR_PAIR(White));
            } else if (map[i][j] == 'P') {
                attron(COLOR_PAIR(Green));
                mvprintw(i, j * 2, "  ");
                attroff(COLOR_PAIR(Green));
            } else if (map[i][j] == 'E') {
                attron(COLOR_PAIR(Red));
                mvprintw(i, j * 2, "  ");
                attroff(COLOR_PAIR(Red));
            } else if (map[i][j] == 'B') {
                attron(COLOR_PAIR(Yellow));
                mvprintw(i, j * 2, "  ");
                attroff(COLOR_PAIR(Yellow));
            } else {
                attron(COLOR_PAIR(Black));
                mvprintw(i, j * 2, "  ");
                attron(COLOR_PAIR(Black));
            }
        }
    }
    attron(COLOR_PAIR(White));
    printText("Score: " + std::to_string(score), 0, 0);
    attroff(COLOR_PAIR(White));
}

void Ncurse::printText(std::string text, int x, int y) {
    mvprintw(y, x, text.c_str(), 0);
}

void Ncurse::printText(std::string text, int x, int y, std::string color) {
    if (color == "white")
        attron(COLOR_PAIR(White));
    else if (color == "green")
        attron(COLOR_PAIR(Green));
    else if (color == "red")
        attron(COLOR_PAIR(Red));
    else if (color == "yellow")
        attron(COLOR_PAIR(Yellow));
    mvprintw(y, x, text.c_str(), 0);
    if (color == "white")
        attroff(COLOR_PAIR(White));
    else if (color == "green")
        attroff(COLOR_PAIR(Green));
    else if (color == "red")
        attroff(COLOR_PAIR(Red));
    else if (color == "yellow")
        attroff(COLOR_PAIR(Yellow));
}

void Ncurse::displayClear() {
    erase();
}

int Ncurse::event() {
    nodelay(stdscr, TRUE);
    int ch = getch();

    switch (ch) {
        case KEY_UP:
            return ac::Core::Input::UP;
            break;
        case KEY_DOWN:
            return ac::Core::Input::DOWN;
            break;
        case KEY_LEFT:
            return ac::Core::Input::LEFT;
            break;
        case KEY_RIGHT:
            return ac::Core::Input::RIGHT;
            break;
        case 27:
            return ac::Core::Input::ESCAPE;
            break;
        case KEY_BACKSPACE:
            return ac::Core::Input::BACKSPACE;
            break;
        case 10:
            return ac::Core::Input::ENTER;
            break;
        default:
            return ch;
            break;
    }
    return ac::Core::Input::NONE;
}

void Ncurse::displayRefresh() {
    refresh();
}

void Ncurse::printLogo() {
    for (int i = 0; i < _logo.size(); i++) {
        printText(_logo[i], 10, i);
    }
}
