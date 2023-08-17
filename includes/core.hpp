/*
** EPITECH PROJECT, 2022
** Core
** File description:
** arcade.hpp
*/

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <dlfcn.h>
#include <vector>
#include <filesystem>
#include <fstream>
#include <ctime>

namespace ac {
    class Core;
    class IDisplayModule;
    class IGameModule;
}

namespace ac {
    class Core  {
        public:
            IDisplayModule *_currentDisplay;
            IGameModule *_currentGame;
            bool _isRunning;
            void *_handleDisplay;
            void *_handleGame;
            int _displayIndex;
            int _game;
            int _selectMenu;
            std::string _userNameWrite;
            int _event;
            int _score;

            typedef struct lib_s {
                std::string name;
                std::string path;
            } lib_t;

            Core(char *libraryName);
            ~Core();

            void *getSym(const std::string symName);
            void getDisplayLibs();
            void getGameLibs();
            void loadDisplay();
            void loadGame();
            int find_index(std::string libraryName);
            void changeLibrary(int index);
            void fillUserName(int key);
            void printHighScores(int offsetY);
            void saveScore();

            //* Getters
            std::string getUserName() { return _userName; };
            std::vector<lib_t> getDisplayList() { return _displayList; };
            std::vector<lib_t> getGameList() { return _gameList; };
            int getNumberOfDisplayLibs() { return _displayList.size(); };
            int getNumberOfGameLibs() { return _gameList.size(); };
            int getLibraryIndex() { return _displayIndex; };

            //* Setters
            void setUserName(std::string userName) { _userName = userName; };
            void setLibraryIndex(int index) { _displayIndex = index; };
            void increaseScore(int score) { _score += score; };

            class CoreException : public std::exception {
                public:
                    CoreException(const std::string &message) throw()
                    : _message(message) {};
                    ~CoreException() throw() {};
                    const char *what() const throw() { return _message.c_str(); };
                private:
                    std::string _message;
            };
            class Input {
                public:
                    Input() = default;
                    ~Input() = default;
                    enum Key {
                        UP = 1,
                        DOWN,
                        LEFT,
                        RIGHT,
                        ESCAPE,
                        ENTER,
                        SPACE,
                        BACKSPACE,
                        NONE,
                        Z,
                        Q,
                        S,
                        D
                    };
                    enum Event {
                        PRESSED,
                        RELEASED
                    };

                    Key key;
                    Event event;
            };
        private:
            std::vector<lib_t> _displayList;
            std::vector<lib_t> _gameList;
            std::vector<Input> _eventList;
            std::string _userName;
    };
    class IDisplayModule {
        public:
            ~IDisplayModule() = default;
            virtual void end () = 0;
            virtual void draw (std::vector<std::string> map, int score) = 0;
            virtual void printText (std::string text, int x, int y) = 0;
            virtual void printText (std::string text, int x, int y, std::string color) = 0;
            virtual void displayRefresh () = 0;
            virtual void displayClear () = 0;
            virtual void printLogo () = 0;
            virtual int event () = 0;
        protected:
        private:
    };
    class IGameModule {
        public:
            ~IGameModule() = default;
            virtual int gameCompute(ac::Core *core) = 0;
            virtual std::vector<std::string> gameGetMap() = 0;

            class Entity {
                public:
                    enum Type {
                        WALL,
                        PLAYER,
                        ENEMY,
                        BONUS,
                        NONE
                    };
                    Entity() = default;
                    Entity(int x, int y,  Type type) : _x(x), _y(y), _type(type) {};
                    ~Entity() = default;

                    Type getType() { return _type; };
                    void setType(Type type) { _type = type; };

                    int getX() { return _x; };
                    void setX(int x) { _x = x; };

                    int getY() { return _y; };
                    void setY(int y) { _y = y; };
                private:
                    Type _type;
                    int _x;
                    int _y;
            };
        protected:
        private:
    };
}
