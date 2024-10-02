/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** IDisplayMenu.hpp
*/

#pragma once
#include <vector>
#include "../src/Tools/Pixel/Pixel.hpp"
#include "../src/Tools/Text/Text.hpp"
#include "IDisplayModule.hpp"

namespace Arcade {
    class IDisplayMenu {
    public:
        virtual std::string getSelectedGraphicLibrary() const = 0;
        virtual std::string getSelectedGameLibrary() const = 0;
        virtual void setPlayerName(const std::string &name) = 0;
        virtual std::string getPlayerName() const = 0;
        virtual void initializeAvailableLibraries(std::vector<std::pair<std::string, std::string>> gameLibraries, std::vector<std::pair<std::string, std::string>> GraphiLibraries) = 0;
        virtual void initializeBackground(IDisplayModule *displayModule) = 0;
        virtual void displayTextOnScreen(IDisplayModule *displayModule) = 0;
        virtual void displayBackgroundImage(IDisplayModule *displayModule) = 0;
        virtual void displayPlayerNameOnScreen(IDisplayModule *displayModule) = 0;
        virtual void handleEvent(Arcade::CommandType event, Arcade::IDisplayModule *displayModule) = 0;
        virtual ~IDisplayMenu() {};
    };
}