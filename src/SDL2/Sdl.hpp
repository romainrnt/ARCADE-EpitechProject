/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** SDL2.hpp
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "../../include/IDisplayModule.hpp"
#include "../Tools/Errors/Exceptions.hpp"
#include "../../include/IType.hpp"
#include "../Tools/Text/Text.hpp"
#include "../Tools/Pixel/Pixel.hpp"

namespace Arcade {
    class LibSDL : public IDisplayModule {
    public:
        LibSDL();
        ~LibSDL() override;
        void drawPixel(Pixel *pixel) override;
        void drawText(Text *text) override;
        void drawBackground() override {};
        void clearScreen() override;
        void refreshScreen() override;
        Arcade::CommandType getInput() override;
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        TTF_Font *_font;
        SDL_Color _color;
        int _rendererW = 0;
        int _rendererH = 0;
    };
    std::map<int, CommandType> SDL_key {
        {SDLK_a, A},
        {SDLK_b, B},
        {SDLK_c, C},
        {SDLK_d, D},
        {SDLK_e, E},
        {SDLK_f, F},
        {SDLK_g, G},
        {SDLK_h, H},
        {SDLK_i, I},
        {SDLK_j, J},
        {SDLK_k, K},
        {SDLK_l, L},
        {SDLK_m, M},
        {SDLK_n, N},
        {SDLK_o, O},
        {SDLK_p, P},
        {SDLK_q, Q},
        {SDLK_r, R},
        {SDLK_s, S},
        {SDLK_t, T},
        {SDLK_u, U},
        {SDLK_v, V},
        {SDLK_w, W},
        {SDLK_x, X},
        {SDLK_y, Y},
        {SDLK_z, Z},
        {SDLK_0, NUM0},
        {SDLK_1, NUM1},
        {SDLK_2, NUM2},
        {SDLK_3, NUM3},
        {SDLK_4, NUM4},
        {SDLK_5, NUM5},
        {SDLK_6, NUM6},
        {SDLK_7, NUM7},
        {SDLK_8, NUM8},
        {SDLK_9, NUM9},
        {SDLK_LEFT, LEFT},
        {SDLK_RIGHT, RIGHT},
        {SDLK_UP, UP},
        {SDLK_DOWN, DOWN},
        {SDLK_KP_ENTER, ENTER},
        {13, ENTER},
        {SDLK_SPACE, SPACE},
        {SDLK_BACKSPACE, BACKSPACE},
        {SDLK_ESCAPE, ESC},
        {SDLK_F1, F1},
        {SDLK_F2, F2},
        {SDLK_F3, F3},
        {SDLK_F4, F4},
        {SDLK_F5, F5},
        {SDLK_F6, F6}
    };
    IDisplayModule *getLibrary();
    LibraryType getLibraryType();
}
