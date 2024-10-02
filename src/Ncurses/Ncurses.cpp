/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Ncurses.cpp
*/

#include "Ncurses.hpp"
#include "../../include/IType.hpp"

Arcade::libraryNcurses::libraryNcurses()
{
    _window = initscr();
    cbreak();
    noecho();
    nodelay(_window, true);
    start_color();
    keypad(stdscr, TRUE);
    init_pair(NCT_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(NCT_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(NCT_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(NCS_BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(NCT_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(NCS_RED, COLOR_RED, COLOR_RED);
    init_pair(NCS_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(NCS_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(NCS_CYAN, COLOR_CYAN, COLOR_CYAN);
    init_pair(NCT_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(NCS_RED, COLOR_RED, COLOR_BLACK);
    init_pair(NCT_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(NCT_BLACK, COLOR_BLACK, COLOR_WHITE);
    init_pair(NCS_WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(NCS_GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(NCS_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
}

Arcade::libraryNcurses::~libraryNcurses()
{
    endwin();
}

extern "C" Arcade::IDisplayModule *getLibrary()
{
    return (new Arcade::libraryNcurses());
}

extern "C" Arcade::LibraryType getLibraryType()
{
    return ((Arcade::LibraryType)Arcade::GRAPHIC);
}

int makeSware(int COLS, int LINES)
{
    int nbExtra = 0;

    if (COLS > LINES)
        nbExtra = (COLS - (LINES * 2)) / 2 + 1;
    return (nbExtra);
}

static int translateColor(Arcade::Color color, bool clr)
{
    switch (color) {
        case Arcade::Color::YELLOW:
            if (clr)
                return (NCT_YELLOW);
            else
                return (NCS_YELLOW);
        case Arcade::Color::RED:
            if (clr)
                return (NCS_RED);
            else
                return (NCS_RED);
        case Arcade::Color::BLUE:
            if (clr)
                return NCT_BLUE;
            else
                return (NCS_BLUE);
        case Arcade::Color::WHITE:
            if (clr)
                return (NCT_WHITE);
            else
                return (NCS_WHITE);
        case Arcade::Color::BLACK:
            if (clr)
                return (NCT_BLACK);
            else
                return (NCS_BLACK);
        case Arcade::Color::CYAN:
            if (clr)
                return (NCT_CYAN);
            else
                return (NCS_CYAN);
        case Arcade::Color::GREEN:
            if (clr)
                return (NCT_GREEN);
            else
                return (NCS_GREEN);
        case Arcade::Color::MAGENTA:
            if (clr)
                return (NCT_MAGENTA);
            else
                return (NCS_MAGENTA);
        case Arcade::Color::TRANSPARENT:
            if (clr)
                return (NCT_BLACK);
            else
                return (NCS_BLACK);
    }
    return (NCS_BLACK);
}

void Arcade::libraryNcurses::drawPixel(Arcade::Pixel* pixel)
{
    if (pixel->getTextColor() == Arcade::Color::BLACK)
        return;
    int windowW, windowH;
    getmaxyx(_window, windowH, windowW);
    float scaleX = windowW / 100.0f;
    float scaleY = windowH / 100.0f;
    float xPosition = scaleX * pixel->getXCoordinate();
    float yPosition = scaleY * pixel->getYCoordinate();
    float middleWidth = windowW / 2.0f;
    float lowerHeight = windowH * 0.6f;

    if (abs(xPosition - middleWidth) < 10 && abs(yPosition - lowerHeight) < 10 && (pixel->getTextColor() == Arcade::Color::GREEN || pixel->getTextColor() == Arcade::Color::BLACK))
        return;

    int startX = static_cast<int>((pixel->getXCoordinate() - pixel->getTextSize() / 2.0f) * scaleX);
    int startY = static_cast<int>((pixel->getYCoordinate() - pixel->getTextSize() / 2.0f) * scaleY);
    int endX = static_cast<int>(pixel->getTextSize() * scaleX);
    int endY = static_cast<int>(pixel->getTextSize() * scaleY);
    int colorPair = translateColor(pixel->getTextColor(), false);
    attron(COLOR_PAIR(colorPair));

    for (int i = startY; i < startY + endY; ++i) {
        for (int j = startX; j < startX + endX; ++j)
            mvwaddch(_window, i, j, ' ');
    }
    attroff(COLOR_PAIR(colorPair));
}

void Arcade::libraryNcurses::drawText(Text *text)
{
    attron(COLOR_PAIR(translateColor(text->getTextColor(), true)));
    mvprintw(LINES * text->getYCoordinate() / 100 - 0.5 * 1, COLS * text->getXCoordinate() / 100 - 0.5 * strlen(text->getTextString().c_str()),"%s", text->getTextString().c_str());
    attroff(COLOR_PAIR(translateColor(text->getTextColor(), true)));
}

void Arcade::libraryNcurses::drawBackground()
{

}

void Arcade::libraryNcurses::clearScreen()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLUE);
    attron(COLOR_PAIR(1));
    for (int y = 0; y < LINES; ++y) {
        for (int x = 0; x < COLS; ++x)
            mvaddch(y, x, ' ');
    }
    attroff(COLOR_PAIR(1));
    refresh();
}

void Arcade::libraryNcurses::refreshScreen()
{
    refresh();
}

Arcade::CommandType Arcade::libraryNcurses::getInput()
{
    int input = getch();
    Arcade::CommandType command = NO_EVENT;

    if (input < 0)
        return (command);
    auto it = NCURSES_key.find(input);
    return (it == NCURSES_key.end() ? Arcade::NO_EVENT : it->second);
}