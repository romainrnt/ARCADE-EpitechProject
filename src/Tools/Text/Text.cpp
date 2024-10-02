/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Text.cpp
*/

#include "Text.hpp"

extern "C" Arcade::Text::Text(int xPos, int yPos, const std::string &str, Color color, int size) :  _textXPosition(xPos), textYPosition(yPos)
{
    _size = size;
    _str = str;
    _isHighlighted = false;
    _color = color;
}

extern "C" Arcade::Text::~Text()
{}

extern "C" bool Arcade::Text::getIsHighlighted() const
{
    return (_isHighlighted);
}

extern "C" void Arcade::Text::setHighlightState(bool state)
{
    _isHighlighted = state;
}

extern "C" int Arcade::Text::getXCoordinate() const
{
    return (_textXPosition);
}

extern "C" void Arcade::Text::setXCoordinate(int xCordinate)
{
    _textXPosition = xCordinate;
}

extern "C" int Arcade::Text::getYCoordinate() const
{
    return (textYPosition);
}

extern "C" void Arcade::Text::setYCoordinate(int yCoordinate)
{
    textYPosition = yCoordinate;
}

extern "C" int Arcade::Text::getTextSize() const
{
    return (_size);
}

extern "C" void Arcade::Text::setTextSize(int textSize)
{
    _size = textSize;
}

extern "C" const std::string &Arcade::Text::getTextString() const
{
    return (_str);
}

extern "C" void Arcade::Text::setTextString(const std::string &text)
{
    _str = text;
}

extern "C" Arcade::Color Arcade::Text::getTextColor() const
{
    return (_color);
}

extern "C" void Arcade::Text::setTextColor(Arcade::Color textColor)
{
    _color = textColor;
}
