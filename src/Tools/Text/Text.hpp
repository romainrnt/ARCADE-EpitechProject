/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Text.hpp
*/

#pragma once
#include <iostream>
#include <algorithm>
#include "../../../include/IType.hpp"

namespace Arcade {
    class Text {
    public:
        Text(int xPos, int yPos, const std::string &str, Color color = WHITE, int size = 1);
        virtual ~Text();
        bool getIsHighlighted() const;
        void setHighlightState(bool state);
        int getXCoordinate() const;
        void setXCoordinate(int xCordinate);
        int getYCoordinate() const;
        void setYCoordinate(int yCoordinate);
        int getTextSize() const;
        void setTextSize(int textSize);
        const std::string &getTextString() const;
        void setTextString(const std::string &text);
        Color getTextColor() const;
        void setTextColor(Arcade::Color textColor);
    private:
        bool _isHighlighted;
        int _textXPosition;
        int textYPosition;
        int _size;
        std::string _str;
        Color _color;
    };
}