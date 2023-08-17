/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** arcade_ncurses
*/

#pragma once

#include <ncurses.h>
#include "../../../includes/core.hpp"

static const int KEY_ESC = 27;

class Ncurse: public ac::IDisplayModule {
    public:
        Ncurse();
        ~Ncurse();
        void end() override;
        void displayClear() override;
        void draw(std::vector<std::string> map, int score) override;
        void printText(std::string text, int x, int y) override;
        void printText(std::string text, int x, int y, std::string color) override;
        int event() override;
        void displayRefresh() override;
        void printLogo() override;

        class NcurseException : public std::exception {
            public:
                NcurseException(std::string const &message) throw () : _message(message) {};
                ~NcurseException() throw () {};
                const char *what() const throw () { return _message.c_str(); };
            private:
                std::string _message;
        };
    private:
        std::vector<std::string> _logo;
};
