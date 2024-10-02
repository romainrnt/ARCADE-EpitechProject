/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Sfml.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <chrono>
#include <cmath>
#include <algorithm>
#include "../../include/IDisplayModule.hpp"
#include "../Tools/Pixel/Pixel.hpp"
#include "../Tools/Text/Text.hpp"
#include "../../include/IType.hpp"
#include "../Tools/Errors/Exceptions.hpp"

namespace Arcade {
    class librarySFML : public IDisplayModule {
    public:
        librarySFML();
        ~librarySFML() override;
        void drawPixel(Pixel *pixel) override;
        void drawText(Text *text) override;
        void drawBackground() override;
        void clearScreen() override;
        void refreshScreen() override;
        Arcade::CommandType getInput() override;
    private:
        sf::RenderWindow _window;
        sf::Sprite _background;
    };
    std::map <int, CommandType> SFML_key {
        {sf::Keyboard::A,      A},
        {sf::Keyboard::B,      B},
        {sf::Keyboard::C,      C},
        {sf::Keyboard::D,      D},
        {sf::Keyboard::E,      E},
        {sf::Keyboard::F,      F},
        {sf::Keyboard::G,      G},
        {sf::Keyboard::H,      H},
        {sf::Keyboard::I,      I},
        {sf::Keyboard::J,      J},
        {sf::Keyboard::K,      K},
        {sf::Keyboard::L,      L},
        {sf::Keyboard::M,      M},
        {sf::Keyboard::N,      N},
        {sf::Keyboard::O,      O},
        {sf::Keyboard::P,      P},
        {sf::Keyboard::Q,      Q},
        {sf::Keyboard::R,      R},
        {sf::Keyboard::S,      S},
        {sf::Keyboard::T,      T},
        {sf::Keyboard::U,      U},
        {sf::Keyboard::V,      V},
        {sf::Keyboard::W,      W},
        {sf::Keyboard::X,      X},
        {sf::Keyboard::Y,      Y},
        {sf::Keyboard::Z,      Z},
        {sf::Keyboard::Num0,   NUM0},
        {sf::Keyboard::Num1,   NUM1},
        {sf::Keyboard::Num2,   NUM2},
        {sf::Keyboard::Num3,   NUM3},
        {sf::Keyboard::Num4,   NUM4},
        {sf::Keyboard::Num5,   NUM5},
        {sf::Keyboard::Num6,   NUM6},
        {sf::Keyboard::Num7,   NUM7},
        {sf::Keyboard::Num8,   NUM8},
        {sf::Keyboard::Num9,   NUM9},
        {sf::Keyboard::Left,   LEFT},
        {sf::Keyboard::Right,  RIGHT},
        {sf::Keyboard::Up,     UP},
        {sf::Keyboard::Down,   DOWN},
        {sf::Keyboard::Enter,  ENTER},
        {sf::Keyboard::Space,  SPACE},
        {sf::Keyboard::BackSpace, BACKSPACE},
        {sf::Keyboard::Escape, ESC},
        {sf::Keyboard::F1,     F1},
        {sf::Keyboard::F2,     F2},
        {sf::Keyboard::F3,     F3},
        {sf::Keyboard::F4,     F4},
        {sf::Keyboard::F5,     F5},
        {sf::Keyboard::F6,     F6},
    };
    IDisplayModule *getLibrary();
    LibraryType getLibraryType();
}