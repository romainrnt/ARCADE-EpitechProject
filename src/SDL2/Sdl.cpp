/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** SDL2.cpp
*/

#include "Sdl.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../include/IType.hpp"

extern "C" Arcade::IDisplayModule *getLibrary()
{
    return (new Arcade::LibSDL());
}

extern "C" Arcade::LibraryType getLibraryType()
{
    return ((Arcade::LibraryType)Arcade::GRAPHIC);
}

static SDL_Color translateColor(Arcade::Color color)
{
    switch (color) {
        case Arcade::Color::YELLOW:
            return {255, 255, 0, 255};
        case Arcade::Color::RED:
            return {255, 0, 0, 255};
        case Arcade::Color::BLUE:
            return {0, 0, 255, 255};
        case Arcade::Color::WHITE:
            return {255, 255, 255, 255};
        case Arcade::Color::BLACK:
            return {0, 0, 0, 255};
        case Arcade::Color::CYAN:
            return {0, 255, 255, 255};
        case Arcade::Color::GREEN:
            return {0, 255, 0, 255};
        case Arcade::Color::MAGENTA:
            return {255, 0, 255, 255};
        case Arcade::Color::TRANSPARENT:
            return {0, 0, 0, 0};
    }
    return {0, 0, 0, 255};
}

Arcade::LibSDL::LibSDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    _font = TTF_OpenFont("assets/font/font.ttf", 30);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
    SDL_RenderClear(_renderer);
}

Arcade::LibSDL::~LibSDL()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Arcade::LibSDL::refreshScreen()
{
    SDL_RenderPresent(_renderer);
}

void Arcade::LibSDL::clearScreen()
{
    auto currentTime = std::chrono::steady_clock::now().time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime).count();

    float t = sin(static_cast<float>(milliseconds) * 0.001f) * 0.5f + 0.5f;
    int red = static_cast<int>(t * 255);

    SDL_SetRenderDrawColor(_renderer, red, 128, 128, 255);
    SDL_RenderClear(_renderer);
}

void Arcade::LibSDL::drawPixel(Pixel* pixel)
{
    if (pixel->getTextColor() == Arcade::Color::BLACK) {
        return;
    }
    int rendererW, rendererH;
    SDL_GetRendererOutputSize(_renderer, &rendererW, &rendererH);
    float scaleX = rendererW / 100.0f;
    float scaleY = rendererH / 100.0f;

    float xPosition = scaleX * pixel->getXCoordinate();
    float yPosition = scaleY * pixel->getYCoordinate();
    float middleWidth = rendererW / 2.0f;
    float lowerHeight = rendererH * 0.6f;
    if (abs(xPosition - middleWidth) < 10 && abs(yPosition - lowerHeight) < 10 && (pixel->getTextColor() == Arcade::Color::GREEN || pixel->getTextColor() == Arcade::Color::BLACK)) {
        return;
    }
    SDL_Rect rect {
        static_cast<int>((pixel->getXCoordinate() - pixel->getTextSize() / 2.0f) * scaleX),
        static_cast<int>((pixel->getYCoordinate() - pixel->getTextSize() / 2.0f) * scaleY),
        static_cast<int>(pixel->getTextSize() * scaleX),
        static_cast<int>(pixel->getTextSize() * scaleY)
    };
    _color = translateColor(pixel->getTextColor());
    SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(_renderer, &rect);
}

void Arcade::LibSDL::drawText(Text* text)
{
    SDL_Rect dstRect;
    TTF_Font* font = _font;
    const char* str = text->getTextString().c_str();
    SDL_Color my_color = translateColor(text->getTextColor());
    SDL_Surface* surface = TTF_RenderText_Solid(font, str, my_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);

    int textW = surface->w;
    int textH = surface->h;
    int rendW, rendH;
    SDL_GetRendererOutputSize(_renderer, &rendW, &rendH);
    dstRect.x = (int)(rendW * text->getXCoordinate() / 100 - 0.5 * textW);
    dstRect.y = (int)(rendH * text->getYCoordinate() / 100 - 0.5 * textH);
    dstRect.w = textW;
    dstRect.h = textH;

    SDL_RenderCopy(_renderer, texture, NULL, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

Arcade::CommandType Arcade::LibSDL::getInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return Arcade::ESC;
            case SDL_KEYUP: {
                auto it = SDL_key.find(event.key.keysym.sym);
                return it == SDL_key.end() ? Arcade::NO_EVENT : it->second;
            }
            default:
                break;
        }
    }
    return Arcade::NO_EVENT;
}
