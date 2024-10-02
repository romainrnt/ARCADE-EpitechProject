/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** IGameModule.hpp
*/

#pragma once
#include "IDisplayModule.hpp"

namespace Arcade {
    class IGameModule {
    public:
        virtual void initializePlayerName(std::string playerName) = 0;
        virtual void drawGraphics(IDisplayModule *displayModule) = 0;
        virtual void handleEvent(CommandType cmd, IDisplayModule *displayModule) = 0;
        virtual void updateGameState(double timeElapsed) = 0;
        virtual ~IGameModule() {};
    };
}