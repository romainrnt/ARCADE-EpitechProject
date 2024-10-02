/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Ncurses.hpp
*/

#pragma once
#include <ncurses.h>
#include <map>
#include <cstring>
#include <chrono>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "../../include/IDisplayModule.hpp"
#define NCT_BLUE 1
#define NCT_WHITE 2
#define NCT_nRED 3
#define NCT_YELLOW 4
#define NCT_BLACK 5
#define NCT_CYAN 6
#define NCT_GREEN 7
#define NCT_MAGENTA 8
#define NCS_BLUE 9
#define NCS_WHITE 10
#define NCS_RED 11
#define NCS_YELLOW 12
#define NCS_BLACK 13
#define NCS_CYAN 14
#define NCS_GREEN 15
#define NCS_MAGENTA 16

namespace Arcade {
    class libraryNcurses : public IDisplayModule {
    private:
        WINDOW *_window;
    public:
        libraryNcurses();
        ~libraryNcurses() override;
        void drawPixel(Pixel *pixel) override;
        void drawText(Text *text) override;
        void drawBackground() override;
        void clearScreen() override;
        void refreshScreen() override;
        Arcade::CommandType getInput() override;
    };
    std::map<int, CommandType> NCURSES_key {
        {'a', A},
        {'b', B},
        {'c', C},
        {'d', D},
        {'e', E},
        {'f', F},
        {'g', G},
        {'h', H},
        {'i', I},
        {'j', J},
        {'k', K},
        {'l', L},
        {'m', M},
        {'n', N},
        {'o', O},
        {'p', P},
        {'q', Q},
        {'r', R},
        {'s', S},
        {'t', T},
        {'u', U},
        {'v', V},
        {'w', W},
        {'x', X},
        {'y', Y},
        {'z', Z},
        {'0', NUM0},
        {'1', NUM1},
        {'2', NUM2},
        {'3', NUM3},
        {'4', NUM4},
        {'5', NUM5},
        {'6', NUM6},
        {'7', NUM7},
        {'8', NUM8},
        {'9', NUM9},
        {260, LEFT},
        {261, RIGHT},
        {259, UP},
        {258, DOWN},
        {10, ENTER},
        {' ', SPACE},
        {0407, BACKSPACE},
        {27, ESC},
        {265, F1},
        {266, F2},
        {267, F3},
        {268, F4},
        {269, F5},
        {270, F6}
    };
    IDisplayModule *getLibrary();
    LibraryType getLibraryType();
}