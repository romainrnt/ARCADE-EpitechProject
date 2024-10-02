/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** main.cpp
*/

#include "src/Tools/Loader/Loader.hpp"
#include "src/Core/Core.hpp"
#include "include/IDisplayMenu.hpp"
#include "src/Tools/Errors/Exceptions.hpp"

static void print_usage()
{
    std::cout << "Usage:\n\t./arcade [path to graphic lib]\n" << "Example:\n\t./arcade lib/arcade_ncurses.so\n";
}

static void handleInput(Arcade::Core &core, Arcade::IDisplayMenu *menu, Arcade::CommandType &event, int &choices, double &dt, Arcade::Loader &loader)
{
    event = core.getGraphicLibrary()->getInput();
    menu->handleEvent(event, core.getGraphicLibrary());
    choices += event == Arcade::ENTER ? 1 : 0;
    core.ChangeLibrary(loader, event);
    if (dt >= double(1.0f / 25.0f)) {
        menu->displayBackgroundImage(core.getGraphicLibrary());
        menu->displayTextOnScreen(core.getGraphicLibrary());
        dt -= double(1.0f / 25.0f);
    }
}

static std::string menuLoop(Arcade::Core &core, Arcade::Loader &loader, Arcade::IDisplayMenu *menu)
{
    Arcade::CommandType event = Arcade::NO_EVENT;
    int choices = 0;
    clock_t start_t;
    clock_t end_t;
    double current_time = 0.0f;
    double dt = 0.0f;

    menu->initializeAvailableLibraries(loader.getAvailableLibraries(Arcade::GAME), loader.getAvailableLibraries(Arcade::GRAPHIC));
    while (event != Arcade::ESC && event != Arcade::CLOSE_WINDOW && choices < 2) {
        start_t = clock();
        handleInput(core, menu, event, choices, dt, loader);
        end_t = clock();
        current_time = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        dt += current_time;
    }
    if (choices < 2 || event == Arcade::ESC || event == Arcade::CLOSE_WINDOW)
        return ("");
    std::string name = core.playerNameInputLoop(loader, menu);
    delete core.getGraphicLibrary();
    core.assignGraphicLibrary(loader.loadSharedLibrary<Arcade::IDisplayModule>(menu->getSelectedGraphicLibrary(), Arcade::GRAPHIC));
    core.assignGameLibrary(loader.loadSharedLibrary<Arcade::IGameModule>(menu->getSelectedGameLibrary(), Arcade::GAME));
    core.assignGameName(loader.getLibraryName(menu->getSelectedGameLibrary()));
    return (name);
}

int main(int ac, char **av)
{
    try {
        Arcade::Core core;
        Arcade::Loader loader;
        std::string name = "Player";
        bool running = true;

        if (ac < 2) {
            print_usage();
            return (84);
        }
        auto *graphicLibrary = loader.loadSharedLibrary<Arcade::IDisplayModule>(av[1], Arcade::GRAPHIC);
        auto *menuLibrary = loader.loadSharedLibrary<Arcade::IDisplayMenu>(std::string("./lib/arcade_menu.so"), Arcade::MENU);
        auto gameLibrary = loader.loadSharedLibrary<Arcade::IGameModule>(std::string("./lib/arcade_snake.so"), Arcade::GAME);
        if (!graphicLibrary || !menuLibrary || !gameLibrary)
            throw Error("Loading base library failed");
        core.assignGraphicLibrary(graphicLibrary);
        while (running && !(name = menuLoop(core, loader, menuLibrary)).empty())
            running = core.GameLoop(loader, name);
        delete (menuLibrary);
        core.deleteLibraries();
        loader.closeAll();
        return (0);
    } catch (const Error &e) {
        return (84);
    }
}