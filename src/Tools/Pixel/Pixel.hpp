/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Pixel.hpp
*/

#pragma once
#include "../../../include/IType.hpp"

namespace Arcade {
    class Pixel {
    public:
        Pixel(int xPos, int yPos, Color color = WHITE, int size = 1, int factor = 5);
        ~Pixel();
        int getXCoordinate() const;
        void setXCoordinate(int xPos);
        int getYCoordinate() const;
        void setYCoordinate(int yPos);
        int getTextSize() const;
        void setTextSize(int size);
        Color getTextColor() const;
        void setTextColor(Color color);
    private:
        int _textXPosition;
        int _textYPosition;
        Color _color;
        int _size;
    };
}