/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** sfml
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "../../../includes/core.hpp"

class Sfml: ac::IDisplayModule {
    public:
        Sfml();
        ~Sfml();
        void end() override;
        void displayClear() override;
        void draw(std::vector<std::string> map, int score) override;
        void printText(std::string text, int x, int y) override;
        void printText(std::string text, int x, int y, std::string color) override;
        int event() override;
        void displayRefresh() override;
        void printLogo() override;

        class SFMLException : public std::exception {
            public:
                SFMLException(std::string const &message) throw () : _message(message) {};
                ~SFMLException() throw () {};
                const char *what() const throw () { return _message.c_str(); };
            private:
                std::string _message;
        };
    private:
        sf::RenderWindow *_window;
        sf::Event _event;
        sf::Font _font;
        sf::Text _text;
        sf::Color _white;
        sf::Image _logoImage;
        sf::Texture _logoTexture;
        sf::Sprite _logoSprite;
};
