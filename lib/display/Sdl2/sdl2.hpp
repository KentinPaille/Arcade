/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** arcade_sdl2
*/

#pragma once

#include "../../../includes/core.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Sdl2: ac::IDisplayModule {
    public:
        Sdl2();
        ~Sdl2();
        void end() override;
        void displayClear() override;
        void draw(std::vector<std::string> map, int score) override;
        void printText(std::string text, int x, int y) override;
        void printText(std::string text, int x, int y, std::string color) override;
        int event() override;
        void displayRefresh() override;
        void printLogo() override;

        class Sdl2Exception : public std::exception {
            public:
                Sdl2Exception(std::string const &message) throw () : _message(message) {};
                ~Sdl2Exception() throw () {};
                const char *what() const throw () { return _message.c_str(); };
            private:
                std::string _message;
        };
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _event;
        TTF_Font *_font;
        SDL_Color _white;
        SDL_Surface *_logo;
};
