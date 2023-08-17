/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** nibbler
*/

#pragma once

#include "../../../includes/core.hpp"

class Nibbler: ac::IGameModule {
    public:
        Nibbler();
        ~Nibbler() = default;
        enum Direction {
            UP = 1,
            DOWN = -1,
            LEFT = 2,
            RIGHT = -2
        };
        Direction _direction;
        Direction _selectDirection;
        std::chrono::system_clock::time_point _startTime;
        std::chrono::system_clock::time_point _endTime;
        int gameCompute(ac::Core *core) override;
        std::vector<std::string> gameGetMap();
        std::vector<std::string> gameGetMap2();
        void setMap(std::vector<std::string> map);
        void setMap2(std::vector<std::string> map);
        void moveNibblerBody(ac::Core *core);
        bool collision();
        bool findFood();
        void setNewFood();
        int getNibblerSize();
        void checkborder();
        void set_new_map();
    private:
        std::vector<std::string> _map;
        std::vector<std::string> _map2;
        std::vector<ac::IGameModule::Entity> _NibblerBody;
        ac::IGameModule::Entity _food;
};
