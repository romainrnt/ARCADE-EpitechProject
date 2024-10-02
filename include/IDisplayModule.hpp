/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** IDisplayModule.hpp
*/

#pragma once
#include <iostream>
#include "IType.hpp"
#include "../src/Tools/Text/Text.hpp"
#include "../src/Tools/Pixel/Pixel.hpp"

namespace Arcade {
    class IDisplayModule {
    public:
        virtual void drawPixel(Pixel *pixelPtr) = 0;
        virtual void drawText(Text *textPtr) = 0;
        virtual void clearScreen() = 0;
        virtual void refreshScreen() = 0;
        virtual Arcade::CommandType getInput() = 0;
        virtual void drawBackground() = 0;
        virtual ~IDisplayModule() {};
    };
}