/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** snake
*/

#pragma once

#include "../../../includes/core.hpp"

class Snake: ac::IGameModule {
    public:
        Snake();
        ~Snake() = default;
        enum Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
        Direction _direction;
        std::chrono::system_clock::time_point _startTime;
        std::chrono::system_clock::time_point _endTime;
        int gameCompute(ac::Core *core) override;
        std::vector<std::string> gameGetMap();
        std::vector<std::string> gameGetMap2();
        void setMap(std::vector<std::string> map);
        void setMap2(std::vector<std::string> map);
        void moveSnakeHead(ac::Core *core);
        bool collision();
        bool findFood();
        void setNewFood();
        int getSnakeSize();
        void checkborder();
    private:
        std::vector<std::string> _map;
        std::vector<std::string> _map2;
        std::vector<ac::IGameModule::Entity> _snakeBody;
        ac::IGameModule::Entity _food;
};
