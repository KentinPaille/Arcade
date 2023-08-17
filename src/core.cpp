/*
** EPITECH PROJECT, 2022
** Core
** File description:
** library.cpp
*/

#include "../includes/core.hpp"

ac::Core::Core(char *libraryName)
: _displayIndex(0), _handleDisplay(nullptr), _handleGame(nullptr) , _currentDisplay(nullptr)
, _isRunning(true), _game(0), _userName("Player"),  _userNameWrite("Player") ,_selectMenu(0), _event(0), _score(0)
{
    getDisplayLibs();
    getGameLibs();

    if (_gameList.size() == 0)
        throw CoreException("No game library found");

    _displayIndex = ac::Core::find_index(libraryName);

    ac::Core::loadDisplay();
    _eventList.push_back({ac::Core::Input::UP, ac::Core::Input::Event::RELEASED});
    _eventList.push_back({ac::Core::Input::DOWN, ac::Core::Input::Event::RELEASED});
}

ac::Core::~Core()
{
    if (_handleDisplay)
        dlclose(_handleDisplay);
    if (_handleGame)
        dlclose(_handleGame);
}

bool isDisplayLibrary(std::string path)
{
    if (dlsym(dlopen(path.c_str(), RTLD_LAZY), "displayEntryPoint") != nullptr)
        return true;
    return false;
}

void ac::Core::getDisplayLibs()
{
    std::filesystem::path displayLibsPath("./lib/");
    for (const auto &entry : std::filesystem::directory_iterator(displayLibsPath)) {
        if (entry.path().extension() == ".so") {
            if (isDisplayLibrary(entry.path())) {
                lib_t displayLib;
                displayLib.path = entry.path();
                displayLib.name = entry.path().stem();
                _displayList.push_back(displayLib);
            }
        }
    }
}

std::string formatGameName(std::string stem)
{
    std::string name = stem;
    size_t pos = name.find("_");
    if (pos != std::string::npos) {
        name.erase(0, pos + 1);
        name[0] = toupper(name[0]);
    }
    return name;
}

void ac::Core::getGameLibs()
{
    std::filesystem::path gameLibsPath("./lib/");
    for (const auto &entry : std::filesystem::directory_iterator(gameLibsPath)) {
        if (entry.path().extension() == ".so") {
            if (!isDisplayLibrary(entry.path())) {
                lib_t gameLib;
                gameLib.path = entry.path();
                gameLib.name = formatGameName(entry.path().stem());
                _gameList.push_back(gameLib);
            }
        }
    }
}

int ac::Core::find_index(std::string libraryName)
{
    if (!isDisplayLibrary(libraryName))
        throw CoreException("Given argument is not a display library");
    int i = 0;
    for (auto &lib : _displayList) {
        if (lib.path == libraryName)
            return i;
        i++;
    }
    throw CoreException("Library not found");
    return (0);
}

void ac::Core::loadDisplay()
{
    if (_handleDisplay)
        dlclose(_handleDisplay);
    _handleDisplay = dlopen(_displayList[_displayIndex].path.c_str(), RTLD_LAZY);
    if (!_handleDisplay)
        throw CoreException(dlerror());
    void *func = dlsym(_handleDisplay, "displayEntryPoint");
    if (!func)
        throw CoreException(dlerror());
    _currentDisplay = nullptr;
    _currentDisplay = ((IDisplayModule *(*)())func)();
}

void *ac::Core::getSym(const std::string symName)
{
    void *func = dlsym(_handleDisplay, symName.c_str());
    if (!func)
        throw CoreException(dlerror());
    return func;
}

void ac::Core::changeLibrary(int index)
{
    if (_displayIndex + index < 0)
        _displayIndex = _displayList.size() - 1;
    else if (_displayIndex + index >= _displayList.size())
        _displayIndex = 0;
    else
        _displayIndex += index;
    ac::Core::loadDisplay();
}

void ac::Core::fillUserName(int key)
{
    if (key == -1)
        _userNameWrite = _userNameWrite.substr(0, _userNameWrite.size() - 1);
    else if (_userNameWrite.size() <= 10)
        _userNameWrite += key;
}

void ac::Core::loadGame()
{
    if (_handleGame)
        dlclose(_handleGame);
    _handleGame = dlopen(_gameList[_game - 1].path.c_str(), RTLD_LAZY);
    if (!_handleGame)
        throw CoreException(dlerror());
    void *func = dlsym(_handleGame, "gameEntryPoint");
    if (!func)
        throw CoreException(dlerror());
    _currentGame = nullptr;
    _currentGame = ((IGameModule *(*)())func)();
}

void ac::Core::printHighScores(int offsetY)
{
    std::ifstream file("./.highscores");
    if (!file)
        return;

    std::string line;
    std::vector<std::string> scores;
    while (std::getline(file, line))
        scores.push_back(line);
    file.close();

    int nbGameLibs = getNumberOfGameLibs();

    _currentDisplay->printText("Highscores: ", 10, offsetY + nbGameLibs + 9);
    for (int i = 0; i < scores.size(); i++) {
        std::vector<std::string> score;
        size_t pos = scores[i].find(":");
        size_t start = 0;

        while (pos != std::string::npos) {
            score.push_back(scores[i].substr(start, pos - start));
            start = pos + 1;
            pos = scores[i].find(":", pos + 1);
        }
        score.push_back(scores[i].substr(start, scores[i].size()));

        _currentDisplay->printText(score[0], 12, offsetY + nbGameLibs + 10 + i);
        _currentDisplay->printText(score[1], 32, offsetY + nbGameLibs + 10 + i);
        _currentDisplay->printText(score[2], 52, offsetY + nbGameLibs + 10 + i);
    }
}

void ac::Core::saveScore(void)
{
    std::fstream file("./.highscores", std::ios::in | std::ios::app);
    std::string line;
    std::vector<std::vector<std::string>> scores;
    while (std::getline(file, line)) {
        std::vector<std::string> score;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ':'))
            score.push_back(token);
        scores.push_back(score);
    }
    file.close();

    std::ofstream newFile("./.highscores", std::ofstream::out | std::ofstream::trunc);
    bool registeredGame = false;
    for (int i = 0; i < scores.size(); i++) {
        if (scores[i][0] == _gameList[_game - 1].name) {
            registeredGame = true;
            if (std::stoi(scores[i][2]) < _score) {
                scores[i][1] = _userName;
                scores[i][2] = std::to_string(_score);
            }
        }
    }
    if (!registeredGame)
        scores.push_back({_gameList[_game - 1].name, _userName, std::to_string(_score)});
    for (int i = 0; i < scores.size(); i++)
        newFile << scores[i][0] << ":" << scores[i][1] << ":" << scores[i][2] << std::endl;
    newFile.close();
}
