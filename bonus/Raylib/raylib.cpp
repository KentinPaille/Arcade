/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** raylib
*/

#include "raylib.hpp"

static const char *WINDOW_NAME = "Arcade";
static const char *LOGO_PATH = "assets/logo/arcadeRaylib.png";

extern "C" Raylib *displayEntryPoint() {
    return new Raylib;
}

Raylib::Raylib()
{
    try {
        InitWindow(1024, 768, WINDOW_NAME);
        SetTargetFPS(60);

        Image logo = LoadImage(LOGO_PATH);
        if (!logo.data)
            throw Raylib::RaylibException("Can't open logo file");

        int imageHeight = GetScreenHeight() / 6;
        int imageWidth = 600;
        ImageResize(&logo, imageWidth, imageHeight);
        _logo = LoadTextureFromImage(logo);
        UnloadImage(logo);

    } catch (Raylib::RaylibException &e) {
        std::cerr << e.what() << std::endl;
        Raylib::~Raylib();
        exit(84);
    }
}

Raylib::~Raylib()
{
    CloseWindow();

    if (_logo.id)
        UnloadTexture(_logo);
}

void Raylib::end()
{
    CloseWindow();
}

void Raylib::displayClear()
{
    ClearBackground(BLACK);
}

void Raylib::draw(std::vector<std::string> map, int score)
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) == '#')
                DrawRectangle(j * 20, i * 20, 20, 20, WHITE);
            if (map.at(i).at(j) == 'B')
                DrawRectangle(j * 20, i * 20, 20, 20, RED);
            if (map.at(i).at(j) == 'P')
                DrawRectangle(j * 20, i * 20, 20, 20, GREEN);
        }
    }
    printText("Score: " + std::to_string(score), 0, 0, "black");
}

void Raylib::printText(std::string text, int x, int y)
{
    DrawText(text.c_str(), x * 10, y * 20, 20, WHITE);
}

void Raylib::printText(std::string text, int x, int y, std::string color)
{
    if (color == "red")
        DrawText(text.c_str(), x * 10, y * 20, 20, RED);
    if (color == "green")
        DrawText(text.c_str(), x * 10, y * 20, 20, GREEN);
    if (color == "blue")
        DrawText(text.c_str(), x * 10, y * 20, 20, BLUE);
    if (color == "black")
        DrawText(text.c_str(), x * 10, y * 20, 20, BLACK);
    if (color == "white")
        DrawText(text.c_str(), x * 10, y * 20, 20, WHITE);
}

int Raylib::event()
{
    int key = GetKeyPressed();
    if (IsKeyPressed(KEY_ESCAPE))
        return (ac::Core::Input::ESCAPE);
    if (IsKeyPressed(KEY_UP))
        return (ac::Core::Input::UP);
    if (IsKeyPressed(KEY_DOWN))
        return (ac::Core::Input::DOWN);
    if (IsKeyPressed(KEY_LEFT))
        return (ac::Core::Input::LEFT);
    if (IsKeyPressed(KEY_RIGHT))
        return (ac::Core::Input::RIGHT);
    if (IsKeyPressed(KEY_ENTER))
        return (ac::Core::Input::ENTER);
    if (IsKeyPressed(KEY_BACKSPACE))
        return (ac::Core::Input::BACKSPACE);
    if (IsKeyPressed(KEY_A))
        return ('q');
    if (IsKeyPressed(KEY_W))
        return ('z');
    if (IsKeyPressed(KEY_Q))
        return ('A');
    if (IsKeyPressed(KEY_Z))
        return ('W');
    if (IsKeyPressed(KEY_S))
        return ('s');
    if (IsKeyPressed(KEY_D))
        return ('d');
    return (key);
}

void Raylib::displayRefresh()
{
    EndDrawing();
}

void Raylib::printLogo()
{
    BeginDrawing();
    int margin = 20;
    int imageWidth = 600;
    DrawTexture(_logo, (GetScreenWidth() - imageWidth) / 2, margin, WHITE);
}
