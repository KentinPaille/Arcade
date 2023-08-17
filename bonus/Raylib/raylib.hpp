/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** raylib
*/

#pragma once

#include "raylib.h"
#include "../../includes/core.hpp"

class Raylib: public ac::IDisplayModule
{
    public:
        Raylib();
        ~Raylib();
        void end() override;
        void displayClear() override;
        void draw(std::vector<std::string> map, int score) override;
        void printText(std::string text, int x, int y) override;
        void printText(std::string text, int x, int y, std::string color) override;
        int event() override;
        void displayRefresh() override;
        void printLogo() override;

        class RaylibException : public std::exception {
            public:
                RaylibException(std::string const &message) throw () : _message(message) {};
                ~RaylibException() throw () {};
                const char *what() const throw () { return _message.c_str(); };
            private:
                std::string _message;
        };
    private:
        Texture2D _logo;
};
