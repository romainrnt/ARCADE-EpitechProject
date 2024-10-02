/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Menu.cpp
*/

#include "../Tools/Loader/Loader.hpp"
#include "../Core/Core.hpp"
#include "Menu.hpp"

extern "C" Arcade::IDisplayMenu *getLibrary()
{
    return new Arcade::Menu();
}

extern "C" Arcade::LibraryType getLibraryType()
{
    return ((Arcade::LibraryType)Arcade::MENU);
}

Arcade::Menu::Menu(): _selectedGameLibrary(""), _selectedGraphicLibrary(""), _playerName(""), _cursorPosition(0), _isRowSelected(false)
{
}

Arcade::Menu::~Menu()
{
}

std::string Arcade::Menu::getSelectedGraphicLibrary() const
{
    return (_selectedGraphicLibrary);
}

std::string Arcade::Menu::getSelectedGameLibrary() const
{
    return (_selectedGameLibrary);
}

void Arcade::Menu::setPlayerName(const std::string &name)
{
    _playerName = name;
}

std::string Arcade::Menu::getPlayerName() const
{
    return (_playerName);
}

void Arcade::Menu::initializeAvailableLibraries(std::vector<std::pair<std::string, std::string>> gameLibraries, std::vector<std::pair<std::string, std::string>> graphicLibraries)
{
    _gameLibraries = gameLibraries;
    _graphicLibraries = graphicLibraries;
}

void Arcade::Menu::initializeBackground(IDisplayModule *displayModule)
{
    (void)displayModule;
}

void Arcade::Menu::displayBackgroundImage(IDisplayModule *displayModule)
{
    Arcade::Pixel libsBox(50, 0, Arcade::TRANSPARENT, 100);
    displayModule->clearScreen();
    displayModule->drawPixel(&libsBox);
}

void Arcade::Menu::displayPlayerNameOnScreen(Arcade::IDisplayModule *displayModule)
{
    Arcade::Text titleGraph(50, 20, "Enter player name :", Arcade::WHITE);
    Arcade::Text titleGame(50, 30, "Finish with ENTER", Arcade::WHITE);
    Arcade::Text playerName(50, 50, _playerName, Arcade::WHITE);
    displayModule->drawText(&titleGraph);
    displayModule->drawText(&titleGame);
    displayModule->drawText(&playerName);
    displayModule->refreshScreen();
}

void Arcade::Menu::displayTextOnScreen(IDisplayModule *displayModule)
{
    Arcade::Text libs(50, 5, "ARCADE", Arcade::BLACK);
    Arcade::Text titleGame(75, 9, "Game Libraries :", Arcade::BLACK);
    Arcade::Text titleGraph(25, 9, "Graphics Libraries :", Arcade::BLACK);
    int i = 0;

    displayModule->drawText(&titleGraph);
    displayModule->drawText(&titleGame);
    displayModule->drawText(&libs);
    for (auto &graphic : _graphicLibraries) {
        Arcade::Text text(25, 20 + (6 * i), graphic.first, Arcade::BLACK);
        if (i++ == _cursorPosition && !_isRowSelected)
            text.setTextColor(Arcade::WHITE);
        displayModule->drawText(&text);
    }
    i = 0;
    for (auto &game : _gameLibraries) {
        Arcade::Text text(75, 20 + (6 * i), game.first, Arcade::BLACK);
        if (i++ == _cursorPosition && _isRowSelected)
            text.setTextColor(Arcade::WHITE);
        displayModule->drawText(&text);
    }
    i = 0;
    displayModule->refreshScreen();
}

void Arcade::Menu::handleEvent(Arcade::CommandType event, Arcade::IDisplayModule *displayModule)
{
    int selectLen = _isRowSelected ? _gameLibraries.size() : _graphicLibraries.size();

    if (event == Arcade::DOWN && _cursorPosition <= selectLen - 2) {
        _cursorPosition++;
    } else if (event == Arcade::DOWN && _cursorPosition >= selectLen - 1) {
        _cursorPosition = 0;
    } else if (event == Arcade::UP && _cursorPosition > 0) {
        _cursorPosition--;
    } else if (event == Arcade::UP && _cursorPosition <= 0) {
        _cursorPosition = selectLen - 1;
    } else if (event == Arcade::ENTER && !_isRowSelected) {
        _selectedGraphicLibrary = _graphicLibraries[_cursorPosition].second;
        _cursorPosition = 0;
        _isRowSelected = !_isRowSelected;
    } else if (event == Arcade::ENTER && _isRowSelected) {
        _selectedGameLibrary = _gameLibraries[_cursorPosition].second;
        _isRowSelected = false;
    }
    (void)displayModule;
}