/*
** EPITECH PROJECT, 2023
** Arcade
** File description:
** snake
*/

#include "snake.hpp"
#include <unistd.h>

extern "C" Snake *gameEntryPoint() {
    return new Snake;
}

Snake::Snake() {
    std::srand(std::time(nullptr));
    _map.push_back("##########################################");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("#                                        #");
    _map.push_back("##########################################");
    _map2 = _map;

    _snakeBody.push_back(Entity(10, 10, Entity::Type::PLAYER));
    _snakeBody.push_back(Entity(9, 10, Entity::Type::PLAYER));
    _snakeBody.push_back(Entity(8, 10, Entity::Type::PLAYER));
    _snakeBody.push_back(Entity(7, 10, Entity::Type::PLAYER));
    setNewFood();
    _startTime = std::chrono::system_clock::now();
    _direction = RIGHT;
}

int Snake::gameCompute(ac::Core *core) {
    _map = _map2;
    moveSnakeHead(core);
    if (collision())
        return 1;
    if (findFood()) {
        core->increaseScore(100);
        _snakeBody.push_back(Entity(_snakeBody.at(_snakeBody.size() - 1).getX(), _snakeBody.at(_snakeBody.size() - 1).getY(), Entity::Type::PLAYER));
        setNewFood();
    }
    checkborder();
    return 0;
}

void Snake::checkborder() {
    if (_snakeBody.at(0).getX() > _map.at(0).size() - 2)
        _snakeBody.at(0).setX(1);
    else if (_snakeBody.at(0).getX() < 1)
        _snakeBody.at(0).setX(_map.at(0).size() - 2);
    if (_snakeBody.at(0).getY() > _map.size() - 2)
        _snakeBody.at(0).setY(1);
    else if (_snakeBody.at(0).getY() < 1)
        _snakeBody.at(0).setY(_map.size() - 2);

    _map[_food.getY()][_food.getX()] = 'B';
    for (auto entity : _snakeBody) {
            _map[entity.getY()][entity.getX()] = 'P';
    }
}

void Snake::setNewFood() {
    _food = Entity(rand() % (_map.at(0).size() - 2) + 1, rand() % (_map.size() - 2) + 1, Entity::Type::BONUS);
    for (auto entity : _snakeBody) {
        if (entity.getX() == _food.getX() && entity.getY() == _food.getY())
            setNewFood();
    }
}

bool Snake::findFood() {
    for (auto entity : _snakeBody) {
        if (entity.getX() == _food.getX() && entity.getY() == _food.getY())
            return true;
    }
    return false;
}

bool Snake::collision() {
    for (int i = 1; i < _snakeBody.size(); i++) {
        if (_snakeBody.at(0).getX() == _snakeBody.at(i).getX() && _snakeBody.at(0).getY() == _snakeBody.at(i).getY())
            return true;
    }
    return false;
}

void Snake::moveSnakeHead(ac::Core *core) {
    if (core->_event == 'z' && _direction != DOWN) {
        _direction = UP;
    }
    if (core->_event == 's' && _direction != UP) {
        _direction = DOWN;
    }
    if (core->_event == 'q' && _direction != RIGHT) {
        _direction = LEFT;
    }
    if (core->_event == 'd' && _direction != LEFT) {
        _direction = RIGHT;
    }
    _endTime = std::chrono::system_clock::now();
    if (_endTime - _startTime > std::chrono::milliseconds(70)) {
        _startTime = std::chrono::system_clock::now();
        for (int i = getSnakeSize() - 1; i > 0; i--) {
            _snakeBody.at(i).setX(_snakeBody.at(i - 1).getX());
            _snakeBody.at(i).setY(_snakeBody.at(i - 1).getY());
        }
        if (_direction == UP)
            _snakeBody.at(0).setY(_snakeBody.at(0).getY() - 1);
        else if (_direction == DOWN)
            _snakeBody.at(0).setY(_snakeBody.at(0).getY() + 1);
        else if (_direction == LEFT)
            _snakeBody.at(0).setX(_snakeBody.at(0).getX() - 1);
        else if (_direction == RIGHT)
            _snakeBody.at(0).setX(_snakeBody.at(0).getX() + 1);
    }
}


int Snake::getSnakeSize() {
    return _snakeBody.size();
}

std::vector<std::string> Snake::gameGetMap() {
    return _map;
}

std::vector<std::string> Snake::gameGetMap2() {
    return _map2;
}

void Snake::setMap(std::vector<std::string> map) {
    _map = map;
}

void Snake::setMap2(std::vector<std::string> map) {
    _map2 = map;
}
