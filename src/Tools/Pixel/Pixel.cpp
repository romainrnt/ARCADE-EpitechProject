/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Pixel.cpp
*/

#include "Pixel.hpp"

extern "C" Arcade::Pixel::Pixel(int xPos, int yPos, Arcade::Color color, int size, int factor) : _textXPosition(xPos), _textYPosition(yPos), _color(color), _size(size)
{
    (void)factor;
}

extern "C" Arcade::Pixel::~Pixel()
{}

extern "C" int Arcade::Pixel::getXCoordinate() const
{
    return (_textXPosition);
}

extern "C" void Arcade::Pixel::setXCoordinate(int xPos)
{
    _textXPosition = xPos;
}

extern "C" int Arcade::Pixel::getYCoordinate() const
{
    return (_textYPosition);
}

extern "C" void Arcade::Pixel::setYCoordinate(int yPos)
{
    _textYPosition = yPos;
}

extern "C" int Arcade::Pixel::getTextSize() const
{
    return (_size);
}

extern "C" void Arcade::Pixel::setTextSize(int size)
{
    _size = size;
}

extern "C" Arcade::Color Arcade::Pixel::getTextColor() const
{
    return (_color);
}

extern "C" void Arcade::Pixel::setTextColor(Arcade::Color color)
{
    _color = color;
}