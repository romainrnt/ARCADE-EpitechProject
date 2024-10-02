/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

extern "C" Arcade::IDisplayModule *getLibrary()
{
    return (new Arcade::librarySFML());
}

extern "C" Arcade::LibraryType getLibraryType()
{
    return ((Arcade::LibraryType)Arcade::GRAPHIC);
}

Arcade::librarySFML::librarySFML()
{
    _window.create(sf::VideoMode(1280, 720), "Arcade");
    _window.setFramerateLimit(40);
    _window.setKeyRepeatEnabled(true);
}

Arcade::librarySFML::~librarySFML()
{
    _window.close();
}

static sf::Color translateColor(Arcade::Color color)
{
    switch (color) {
        case Arcade::Color::YELLOW:
            return (sf::Color::Yellow);
        case Arcade::Color::RED:
            return (sf::Color::Red);
        case Arcade::Color::BLUE:
            return (sf::Color::Blue);
        case Arcade::Color::WHITE:
            return (sf::Color::White);
        case Arcade::Color::BLACK:
            return (sf::Color::Black);
        case Arcade::Color::CYAN:
            return (sf::Color::Cyan);
        case Arcade::Color::GREEN:
            return (sf::Color::Green);
        case Arcade::Color::MAGENTA:
            return (sf::Color::Magenta);
        case Arcade::Color::TRANSPARENT:
            return (sf::Color::Transparent);
    }
    return (sf::Color::Black);
}

void Arcade::librarySFML::drawPixel(Arcade::Pixel *pixel)
{
    if (pixel->getTextColor() == Arcade::Color::BLACK) {
        return;
    }
    float xPosition = _window.getSize().x * (float)pixel->getXCoordinate() / 100;
    float yPosition = _window.getSize().y * (float)pixel->getYCoordinate() / 100;
    float middleWidth = _window.getSize().x / 2.0f;
    float lowerHeight = _window.getSize().y * 0.6f;
    if (abs(xPosition - middleWidth) < 10 && abs(yPosition - lowerHeight) < 10 && (pixel->getTextColor() == Arcade::Color::GREEN || pixel->getTextColor() == Arcade::Color::BLACK)) {
        return;
    }
    sf::RectangleShape toDraw;
    sf::FloatRect textRect;
    float sizeX = 20.0f;
    float sizeY = 20.0f;
    toDraw.setSize(sf::Vector2f(sizeX, sizeY));
    textRect = toDraw.getLocalBounds();
    toDraw.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    toDraw.setPosition(xPosition, yPosition);
    toDraw.setFillColor(translateColor(pixel->getTextColor()));
    _window.draw(toDraw);
}

void Arcade::librarySFML::drawText(Arcade::Text *text)
{
    sf::Text toDraw;
    sf::Font font;
    sf::FloatRect textRect;

    font.loadFromFile("assets/font/font.ttf");
    toDraw.setFont(font);
    toDraw.setCharacterSize(text->getTextSize() * 20);
    toDraw.setString(text->getTextString());
    textRect = toDraw.getLocalBounds();
    toDraw.setOrigin(textRect.width / 2.0f,textRect.top  + textRect.height / 2.0f);
    toDraw.setPosition(_window.getSize().x * (float)text->getXCoordinate() / 100, _window.getSize().y * (float)text->getYCoordinate() / 100);
    toDraw.setFillColor(translateColor(text->getTextColor()));
    _window.draw(toDraw);
}

void Arcade::librarySFML::drawBackground()
{}

void Arcade::librarySFML::clearScreen()
{
    auto currentTime = std::chrono::steady_clock::now().time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime).count();

    float t = sin(static_cast<float>(milliseconds) * 0.001f) * 0.5f + 0.5f;
    int red = static_cast<int>(t * 255);

    _window.clear(sf::Color(red, 128, 128, 255));
}

void Arcade::librarySFML::refreshScreen()
{
    _window.display();
}

Arcade::CommandType Arcade::librarySFML::getInput()
{
    sf::Event event;
    event.type = sf::Event::MouseLeft;

    _window.pollEvent((sf::Event &)event);
    if (event.type == sf::Event::Closed) {
        return (Arcade::CLOSE_WINDOW);
    }
    if (event.type == sf::Event::KeyReleased) {
        auto it = SFML_key.find(event.key.code);
        return it == SFML_key.end() ? Arcade::NO_EVENT : it->second;
    } else {
        return (Arcade::NO_EVENT);
    }
}