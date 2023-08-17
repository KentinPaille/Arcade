/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** nibbler
*/

#include "nibbler.hpp"
#include <unistd.h>

extern "C" Nibbler *gameEntryPoint() {
    return new Nibbler;
}

Nibbler::Nibbler() {
    std::srand(std::time(nullptr));
    _map.push_back("###################");
    _map.push_back("#                 #");
    _map.push_back("# ### # ### # ### #");
    _map.push_back("# ### #     # ### #");
    _map.push_back("# ### # # # # ### #");
    _map.push_back("#     # # # #     #");
    _map.push_back("# ##### # # ##### #");
    _map.push_back("# #             # #");
    _map.push_back("# # ##### ##### # #");
    _map.push_back("#                 #");
    _map.push_back("# ##### ### ##### #");
    _map.push_back("#       ###       #");
    _map.push_back("# ### # ### # ### #");
    _map.push_back("# ### #     # ### #");
    _map.push_back("# ### # ### # ### #");
    _map.push_back("#     # ### #     #");
    _map.push_back("# ##### ### ##### #");
    _map.push_back("#                 #");
    _map.push_back("###################");
    _map2 = _map;

    _NibblerBody.push_back(Entity(10, 1, Entity::Type::PLAYER));
    _NibblerBody.push_back(Entity(9, 1, Entity::Type::PLAYER));
    _NibblerBody.push_back(Entity(8, 1, Entity::Type::PLAYER));
    _NibblerBody.push_back(Entity(7, 1, Entity::Type::PLAYER));

    setNewFood();
    _startTime = std::chrono::system_clock::now();
    _direction = RIGHT;
    _selectDirection = RIGHT;
}

void Nibbler::set_new_map() {
    _map.clear();
    _map2.clear();
    _map.push_back("#########################################");
    _map.push_back("#                 ###         ##        #");
    _map.push_back("# ### # ### # ### ### #### ## ## ## ### #");
    _map.push_back("# ### #     # ### ### #### ##    ## ### #");
    _map.push_back("# ### # # # # ###     ####    ##        #");
    _map.push_back("#     # # # #     ###       ##### ##### #");
    _map.push_back("# ##### # # ##### ### ##### ##### ##### #");
    _map.push_back("# #             # ###       #####       #");
    _map.push_back("# # ##### ##### #  ## #####  #### # #####");
    _map.push_back("#                                     ###");
    _map.push_back("# ##### ### ##### #### ### ### ### ## ###");
    _map.push_back("#       ###       ###  ###              #");
    _map.push_back("# ### # ### # ###           ####### ## ##");
    _map.push_back("# ### #     # ###  ##### ## ####### ##  #");
    _map.push_back("# ### # ### # ###      #                #");
    _map.push_back("#     # ### #      ### #### #######  ## #");
    _map.push_back("# ##### ### #####  ### #### #######  ## #");
    _map.push_back("#                                       #");
    _map.push_back("#########################################");
    _map2 = _map;

    _NibblerBody.clear();

    _NibblerBody.push_back(Entity(10, 1, Entity::Type::PLAYER));
    _NibblerBody.push_back(Entity(9, 1, Entity::Type::PLAYER));
    _NibblerBody.push_back(Entity(8, 1, Entity::Type::PLAYER));
    _NibblerBody.push_back(Entity(7, 1, Entity::Type::PLAYER));

    setNewFood();
    _direction = RIGHT;
    _selectDirection = RIGHT;
}

int Nibbler::gameCompute(ac::Core *core) {
    _map = _map2;
    moveNibblerBody(core);
    if (collision())
        return 1;
    if (findFood()) {
        core->increaseScore(100);
        _NibblerBody.push_back(Entity(_NibblerBody.at(_NibblerBody.size() - 1).getX(), _NibblerBody.at(_NibblerBody.size() - 1).getY(), Entity::Type::PLAYER));
        setNewFood();
        if (core->_score == 1000)
            set_new_map();
    }
    checkborder();
    usleep(10000);
    return 0;
}

void Nibbler::checkborder() {

    _map[_food.getY()][_food.getX()] = 'B';
    for (auto entity : _NibblerBody) {
            _map[entity.getY()][entity.getX()] = 'P';
    }
}

void Nibbler::setNewFood() {
    _food = Entity(rand() % (_map.at(0).size() - 2) + 1, rand() % (_map.size() - 2) + 1, Entity::Type::BONUS);
    for (auto entity : _NibblerBody) {
        if (entity.getX() == _food.getX() && entity.getY() == _food.getY())
            setNewFood();
    }

    if (_map.at(_food.getY()).at(_food.getX()) == '#')
        setNewFood();
}

bool Nibbler::findFood() {
    for (auto entity : _NibblerBody) {
        if (entity.getX() == _food.getX() && entity.getY() == _food.getY())
            return true;
    }
    return false;
}

bool Nibbler::collision() {
    for (int i = 1; i < _NibblerBody.size() ; i++) {
        if (_NibblerBody.at(0).getX() == _NibblerBody.at(i).getX() && _NibblerBody.at(0).getY() == _NibblerBody.at(i).getY()) {
            return true;
        }
    }
    return false;
}

void Nibbler::moveNibblerBody(ac::Core *core) {
    if (core->_event == 'z' && _direction != DOWN) {
        _selectDirection = UP;
    }
    if (core->_event == 's' && _direction != UP) {
        _selectDirection = DOWN;
    }
    if (core->_event == 'q' && _direction != RIGHT) {
        _selectDirection = LEFT;
    }
    if (core->_event == 'd' && _direction != LEFT) {
        _selectDirection = RIGHT;
    }
    _endTime = std::chrono::system_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count() > 80) {
        _startTime = std::chrono::system_clock::now();
        if (_selectDirection == UP && _map.at(_NibblerBody.at(0).getY() - 1).at(_NibblerBody.at(0).getX()) != '#')
            _direction = UP;
        if (_selectDirection == DOWN && _map.at(_NibblerBody.at(0).getY() + 1).at(_NibblerBody.at(0).getX()) != '#')
            _direction = DOWN;
        if (_selectDirection == LEFT && _map.at(_NibblerBody.at(0).getY()).at(_NibblerBody.at(0).getX() - 1) != '#')
            _direction = LEFT;
        if (_selectDirection == RIGHT && _map.at(_NibblerBody.at(0).getY()).at(_NibblerBody.at(0).getX() + 1) != '#')
            _direction = RIGHT;

        if ((_direction == UP && _map.at(_NibblerBody.at(0).getY() - 1).at(_NibblerBody.at(0).getX()) != '#') ||
            (_direction == DOWN && _map.at(_NibblerBody.at(0).getY() + 1).at(_NibblerBody.at(0).getX()) != '#') ||
            (_direction == LEFT && _map.at(_NibblerBody.at(0).getY()).at(_NibblerBody.at(0).getX() - 1) != '#') ||
            (_direction == RIGHT && _map.at(_NibblerBody.at(0).getY()).at(_NibblerBody.at(0).getX() + 1) != '#')) {
            for (int i = getNibblerSize() - 1; i > 0; i--) {
                _NibblerBody.at(i).setX(_NibblerBody.at(i - 1).getX());
                _NibblerBody.at(i).setY(_NibblerBody.at(i - 1).getY());
            }
        }
        if (_direction == UP && _map.at(_NibblerBody.at(0).getY() - 1).at(_NibblerBody.at(0).getX()) != '#')
            _NibblerBody.at(0).setY(_NibblerBody.at(0).getY() - 1);
        if (_direction == DOWN && _map.at(_NibblerBody.at(0).getY() + 1).at(_NibblerBody.at(0).getX()) != '#')
            _NibblerBody.at(0).setY(_NibblerBody.at(0).getY() + 1);
        if (_direction == LEFT && _map.at(_NibblerBody.at(0).getY()).at(_NibblerBody.at(0).getX() - 1) != '#')
            _NibblerBody.at(0).setX(_NibblerBody.at(0).getX() - 1);
        if (_direction == RIGHT && _map.at(_NibblerBody.at(0).getY()).at(_NibblerBody.at(0).getX() + 1) != '#')
            _NibblerBody.at(0).setX(_NibblerBody.at(0).getX() + 1);
    }
}

int Nibbler::getNibblerSize() {
    return _NibblerBody.size();
}

std::vector<std::string> Nibbler::gameGetMap() {
    return _map;
}

std::vector<std::string> Nibbler::gameGetMap2() {
    return _map2;
}

void Nibbler::setMap(std::vector<std::string> map) {
    _map = map;
}

void Nibbler::setMap2(std::vector<std::string> map) {
    _map2 = map;
}
