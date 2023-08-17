/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** sfml
*/

#include "sfml.hpp"

static const std::string WINDOW_NAME = "Arcade";
static const std::string FONT_PATH = "assets/fonts/RetroGaming.ttf";
static const std::string LOGO_PATH = "assets/logo/arcadeSFML.png";

extern "C" Sfml *displayEntryPoint() {
    return new Sfml;
}

Sfml::Sfml()
{
    try {
        _window = new sf::RenderWindow(sf::VideoMode(1024, 768), WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close);
        if (!_window)
            throw Sfml::SFMLException("Error: Error while creating window");
        _window->setFramerateLimit(60);
        if (!_font.loadFromFile(FONT_PATH))
            throw Sfml::SFMLException("Error: Font not found");
        _text.setFont(_font);
        _text.setCharacterSize(20);
        _text.setFillColor(sf::Color::White);
        _white = sf::Color::White;

        if (!_logoImage.loadFromFile(LOGO_PATH))
            throw Sfml::SFMLException("Error: Logo not found");
        _logoTexture.loadFromImage(_logoImage);
        _logoSprite.setTexture(_logoTexture);

    } catch (Sfml::SFMLException &e) {
        std::cerr << e.what() << std::endl;
        Sfml::~Sfml();
        exit(84);
    }
}

Sfml::~Sfml()
{
    if (_window)
        delete _window;

    if (_font.loadFromFile(FONT_PATH))
        _font.~Font();

    if (_logoImage.loadFromFile(LOGO_PATH)) {
        _logoImage.~Image();
        _logoTexture.~Texture();
        _logoSprite.~Sprite();
    }
}

void Sfml::end()
{
    _window->close();
}

void Sfml::displayClear()
{
    _window->clear();
}

void Sfml::draw(std::vector<std::string> map, int score)
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '#')
                _text.setFillColor(sf::Color::White);
            else if (map[i][j] == 'B')
                _text.setFillColor(sf::Color::Red);
            else if (map[i][j] == 'P')
                _text.setFillColor(sf::Color::Green);
            else if (map[i][j] == ' ')
                _text.setFillColor(sf::Color::Black);
            _text.setString(map[i][j]);
            _text.setPosition(j * 20, 20 + i * 20);
            _window->draw(_text);
        }
    }
    _text.setFillColor(sf::Color::White);
    _text.setString("Score: " + std::to_string(score));
    _text.setPosition(0, 0);
    _window->draw(_text);
}

void Sfml::printText(std::string text, int x, int y)
{
    _text.setString(text);
    _text.setPosition(x*12, y*20);
    _window->draw(_text);
}

void Sfml::printText(std::string text, int x, int y, std::string color)
{
    if (color == "white")
        _text.setFillColor(sf::Color::White);
    else if (color == "yellow")
        _text.setFillColor(sf::Color::Yellow);
    else if (color == "red")
        _text.setFillColor(sf::Color::Red);
    else if (color == "green")
        _text.setFillColor(sf::Color::Green);
    else if (color == "blue")
        _text.setFillColor(sf::Color::Blue);
    else if (color == "black")
        _text.setFillColor(sf::Color::Black);
    _text.setString(text);
    _text.setPosition(x * 12, y * 20);
    _window->draw(_text);
}

int Sfml::event()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::Escape)
                return ac::Core::Input::ESCAPE;
            if (_event.key.code == sf::Keyboard::Left)
                return ac::Core::Input::LEFT;
            if (_event.key.code == sf::Keyboard::Right)
                return ac::Core::Input::RIGHT;
            if (_event.key.code == sf::Keyboard::Up)
                return ac::Core::Input::UP;
            if (_event.key.code == sf::Keyboard::Down)
                return ac::Core::Input::DOWN;
            if (_event.key.code == sf::Keyboard::Space)
                return ac::Core::Input::SPACE;
            if (_event.key.code == sf::Keyboard::Return)
                return ac::Core::Input::ENTER;
            if (_event.key.code == sf::Keyboard::BackSpace)
                return ac::Core::Input::BACKSPACE;
            else
                return (_event.key.code + 97);
        }
    }
    return (0);
}

void Sfml::displayRefresh()
{
    _window->display();
}

void Sfml::printLogo()
{
    int margin = 20;
    int imageWidth = _logoImage.getSize().x;
    _logoSprite.setPosition((_window->getSize().x - imageWidth) / 2, margin);
    _window->draw(_logoSprite);
}
