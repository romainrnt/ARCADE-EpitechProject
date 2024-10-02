/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Menu.hpp
*/

#pragma once
#include "../../include/IDisplayMenu.hpp"
#include <memory>

namespace Arcade {
    class Menu : public IDisplayMenu {
    public:
        Menu();
        ~Menu();
        void initializeAvailableLibraries(std::vector<std::pair<std::string, std::string>> gameLibraries, std::vector<std::pair<std::string, std::string>> graphicLibraries) override;
        void displayTextOnScreen(IDisplayModule *displayModule) override;
        void handleEvent(Arcade::CommandType event, Arcade::IDisplayModule *displayModule) override;
        std::string getSelectedGraphicLibrary() const override;
        std::string getSelectedGameLibrary() const override;
        void setPlayerName(const std::string &name) override;
        std::string getPlayerName() const override;
        void initializeBackground(IDisplayModule *displayModule) override;
        void displayBackgroundImage(IDisplayModule *displayModule) override;
        void displayPlayerNameOnScreen(IDisplayModule *displayModule) override;
    private:
        std::vector<std::pair<std::string, std::string>> _gameLibraries;
        std::vector<std::pair<std::string, std::string>> _graphicLibraries;
        std::string _selectedGameLibrary;
        std::string _selectedGraphicLibrary;
        std::string _playerName;
        int _cursorPosition;
        bool _isRowSelected;
    };
    IDisplayModule *getLibrary();
    LibraryType getLibraryType();
}