/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Core.cpp
*/

#include "Core.hpp"

void Arcade::Core::assignGraphicLibrary(Arcade::IDisplayModule *graphicLibrary)
{
    _graphicLibrary = graphicLibrary;
}

void Arcade::Core::assignGameLibrary(Arcade::IGameModule *gameLibrary)
{
    _gameLibrary = gameLibrary;
}

void Arcade::Core::assignGameName(const std::string &nameGame)
{
    _gameName = nameGame;
}

void Arcade::Core::ChangeLibrary(Arcade::Loader &loader, Arcade::CommandType event)
{
    const std::array<Arcade::CommandType, 4> libEvent = {
        Arcade::CommandType::NUM0,
        Arcade::CommandType::NUM1,
        Arcade::CommandType::NUM2,
        Arcade::CommandType::NUM3
    };
    if (std::find(libEvent.begin(), libEvent.end(), event) == libEvent.end()) {
        return;
    }
    switch (event) {
    case Arcade::CommandType::NUM0:
        _graphicLibrary = loader.loadNextGraphicLibrary(true);
        assignGraphicLibrary(getGraphicLibrary());
        break;
    case Arcade::CommandType::NUM1:
        _graphicLibrary = loader.loadNextGraphicLibrary(false);
        assignGraphicLibrary(_graphicLibrary);
        break;
    case Arcade::CommandType::NUM2:
        _gameLibrary = loader.loadNextGameLibrary(true);
        getGameLibrary()->initializePlayerName(_playerName);
        break;
    case Arcade::CommandType::NUM3:
        _gameLibrary = loader.loadNextGameLibrary(false);
        getGameLibrary()->initializePlayerName(_playerName);
        break;
    }
}

bool Arcade::Core::GameLoop(Loader &loader, std::string &playerName)
{
    Arcade::CommandType cmd = NO_EVENT;
    double current_time = 0.0f;
    double dt = 0.0f;
    bool should_continue = true;

    _gameLibrary->initializePlayerName(playerName);
    while (should_continue) {
        auto start_t = std::chrono::high_resolution_clock::now();
        cmd = _graphicLibrary->getInput();
        _gameLibrary->handleEvent(cmd, _graphicLibrary);
        ChangeLibrary(loader, cmd);
        current_time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_t).count();
        dt += current_time;
        if (dt >= 1.0 / 25.0) {
            _graphicLibrary->clearScreen();
            _gameLibrary->drawGraphics(_graphicLibrary);
            _graphicLibrary->refreshScreen();
            dt = 0.0f;
        }
        should_continue = (cmd != Arcade::CommandType::CLOSE_WINDOW && cmd != Arcade::CommandType::ESC && cmd != Arcade::CommandType::SPACE);
        _gameLibrary->updateGameState(current_time);
    }
    return (cmd != Arcade::CommandType::ESC && cmd != Arcade::CommandType::CLOSE_WINDOW);
}

std::string Arcade::Core::playerNameInputLoop(Arcade::Loader &loader, Arcade::IDisplayMenu *menu)
{
    Arcade::CommandType event = Arcade::NO_EVENT;
    std::string name;
    auto prev_time = std::chrono::high_resolution_clock::now();
    double dt = 0.0;
    while (event != Arcade::ESC && event != Arcade::ENTER && event != Arcade::CLOSE_WINDOW) {
        auto current_time = std::chrono::high_resolution_clock::now();
        dt += std::chrono::duration_cast<std::chrono::duration<double>>(current_time - prev_time).count();
        prev_time = current_time;
        event = getGraphicLibrary()->getInput();
        if (CoreKeyMap.find(event) != CoreKeyMap.end())
            name.push_back(CoreKeyMap.find(event)->second);
        ChangeLibrary(loader, event);
        if (dt >= double(1.0f / 25.0f)) {
            menu->setPlayerName(name);
            menu->displayBackgroundImage(getGraphicLibrary());
            menu->displayPlayerNameOnScreen(getGraphicLibrary());
            dt -= double(1.0f / 25.0f);
        }
    }
    _playerName = name;
    if (name.empty())
        return ("unknown");
    else
        return (name);
}

void Arcade::Core::deleteLibraries()
{
    delete (_gameLibrary);
    delete (_graphicLibrary);
}
