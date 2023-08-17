/*
** EPITECH PROJECT, 2022
** Core
** File description:
** arcade_sdl2.cpp
*/

#include <iostream>

#include "sdl2.hpp"

static const char *WINDOW_NAME = "Arcade";
static const char *FONT_PATH = "assets/fonts/RetroGaming.ttf";
static const char *LOGO_PATH = "assets/logo/arcadeSDL2.bmp";

extern "C" Sdl2 *displayEntryPoint() {
    return new Sdl2;
}

Sdl2::Sdl2()
: _window(nullptr), _renderer(nullptr), _font(nullptr), _logo(nullptr)
{
    try {
        SDL_Init(SDL_INIT_VIDEO);
        TTF_Init();
        _window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
        if (!_window)
            throw Sdl2::Sdl2Exception("Can't create window");
        _renderer = SDL_CreateRenderer(_window, -1, 0);
        if (!_renderer)
            throw Sdl2::Sdl2Exception("Can't create renderer");

        _font = TTF_OpenFont(FONT_PATH, 20);
        if (!_font)
            throw Sdl2::Sdl2Exception("Can't open font file");
        _white = {255, 255, 255};

        SDL_Event event;
        _event = event;

        _logo = SDL_LoadBMP(LOGO_PATH);
        if (!_logo)
            throw Sdl2::Sdl2Exception("Can't open logo file");

        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
        SDL_RenderPresent(_renderer);
    } catch (Sdl2::Sdl2Exception &e) {
        std::cerr << e.what() << std::endl;
        Sdl2::~Sdl2();
        exit(84);
    }
}

Sdl2::~Sdl2() {
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    if (_font)
        TTF_CloseFont(_font);
    if (_logo)
        SDL_FreeSurface(_logo);
    TTF_Quit();
    SDL_Quit();
    _renderer = nullptr;
    _window = nullptr;
}

void Sdl2::end() {
    Sdl2::~Sdl2();
}

void Sdl2::printText(std::string text, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(_font, text.c_str(), _white);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);

    int texWidth, texHeight;
    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);
    SDL_Rect rect = { (x * 10), (y * 26), texWidth, texHeight };

    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Sdl2::printText(std::string text, int x, int y, std::string color) {
    SDL_Surface *surface = TTF_RenderText_Solid(_font, text.c_str(), {0, 0, 0});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);

    int texWidth, texHeight;
    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);
    SDL_Rect rect = { (x * 10), (y * 26), texWidth, texHeight };

    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Sdl2::draw(std::vector<std::string> map, int score) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '#') {
                SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
                SDL_Rect rect = { (j * 22), (i * 22), 22, 22 };
                SDL_RenderFillRect(_renderer, &rect);
            }
            if (map[i][j] == 'B') {
                SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
                SDL_Rect rect = { (j * 22), (i * 22), 22, 22 };
                SDL_RenderFillRect(_renderer, &rect);
            }
            if (map[i][j] == 'P') {
                SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
                SDL_Rect rect = { (j * 22), (i * 22), 22, 22 };
                SDL_RenderFillRect(_renderer, &rect);
            }
            if (map[i][j] == 'E') {
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
                SDL_Rect rect = { (j * 22), (i * 22), 22, 22 };
                SDL_RenderFillRect(_renderer, &rect);
            }
            if (map[i][j] == ' ') {
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
                SDL_Rect rect = { (j * 22), (i * 22), 22, 22 };
                SDL_RenderFillRect(_renderer, &rect);
            }
        }
    }
    printText("Score: " + std::to_string(score), 0, 0, "black");
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
}

void Sdl2::displayClear() {
    SDL_RenderClear(_renderer);
}

void Sdl2::displayRefresh() {
    SDL_RenderPresent(_renderer);
}

int Sdl2::event() {
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            return ac::Core::Input::ESCAPE;
        }
        if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_UP:
                    return ac::Core::Input::UP;
                    break;
                case SDLK_DOWN:
                    return ac::Core::Input::DOWN;
                    break;
                case SDLK_LEFT:
                    return ac::Core::Input::LEFT;
                    break;
                case SDLK_RIGHT:
                    return ac::Core::Input::RIGHT;
                    break;
                case SDLK_RETURN:
                    return ac::Core::Input::ENTER;
                    break;
                case SDLK_ESCAPE:
                    return ac::Core::Input::ESCAPE;
                    break;
                case SDLK_SPACE:
                    return ac::Core::Input::SPACE;
                    break;
                default:
                    return _event.key.keysym.sym;
                    break;
            }
        }
    }
    return ac::Core::Input::NONE;
}

void Sdl2::printLogo() {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, _logo);
    SDL_Rect rect = { 0, 0, 1024, 180 };
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
