/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Loader.cpp
*/

#include "Loader.hpp"

Arcade::Loader::~Loader()
{
    if (loadMenuLibrary)
        dlclose(loadMenuLibrary);
    if (loadGraphicLibraries)
        dlclose(loadGraphicLibraries);
    if (loadGameLibraries)
        dlclose(loadGameLibraries);
}

std::vector<std::pair<std::string, std::string>> Arcade::Loader::getAvailableLibraries(Arcade::LibraryType type)
{
    std::string name;
    std::vector<std::pair<std::string, std::string>> libraries;

    for (const auto &p : std::filesystem::directory_iterator("./lib")) {
        if (p.path().extension() == ".so") {
            void *sharedLibrary = dlopen(p.path().c_str(), RTLD_NOW);
            if (sharedLibrary) {
                auto getLibraryType = reinterpret_cast<LibraryType (*)()>(dlsym(sharedLibrary, "getLibraryType"));
                if (getLibraryType() == type) {
                    std::pair<std::string, std::string> pathName;
                    pathName.second = p.path().string();
                    name = p.path().stem().string().substr(p.path().stem().string().find('_') + 1);
                    pathName.first = name.substr(0, name.find('.'));
                    libraries.push_back(pathName);
                }
                dlclose(sharedLibrary);
            }
        }
    }
    return (libraries);
}

std::string Arcade::Loader::getLibraryName(std::basic_string<char> fp)
{
    const std::filesystem::path path(fp);
    const std::string extension = path.extension().string();

    if (extension == ".so") {
        const std::string filename = path.stem().string();
        const size_t pos = filename.find_first_of('_');
        if (pos != std::string::npos)
            return (filename.substr(pos + 1));
    }
    return ("");
}

Arcade::IDisplayModule *Arcade::Loader::loadNextGraphicLibrary(bool direction)
{
    std::string toLoad;
    std::vector<std::pair<std::string, std::string>> libraries = getAvailableLibraries(Arcade::GRAPHIC);
    auto it = std::find_if(libraries.begin(), libraries.end(), [&](const std::pair<std::string, std::string> &element)
    {return element.second == loadGraphicsName;});

    if (libraries.empty())
        throw Error("No graphic library found.");
    if (it == libraries.end())
        throw Error("Failed to find currently loaded graphic library in available libraries.");
    std::size_t currentIndex = std::distance(libraries.begin(), it);
    std::size_t nextIndex = (direction ? currentIndex + 1 : currentIndex - 1) % libraries.size();
    toLoad = libraries[nextIndex].second;
    return (loadSharedLibrary<IDisplayModule>(toLoad, Arcade::GRAPHIC));
}

Arcade::IGameModule *Arcade::Loader::loadNextGameLibrary(bool direction)
{
    std::vector<std::pair<std::string, std::string>> libraries = getAvailableLibraries(Arcade::GAME);
    std::vector<std::string> librariesNames(libraries.size());
    std::transform(libraries.begin(), libraries.end(), librariesNames.begin(),
                   [](const auto &libraries) { return (libraries.second); });
    auto it = std::find(librariesNames.begin(), librariesNames.end(), loadGameName);
    if (it == librariesNames.end())
        throw Error("Failed to find currently loaded game library in available libraries.");
    const auto index = std::distance(librariesNames.begin(), it);
    const auto nextIndex = direction ? (index + 1) % librariesNames.size() : (index == 0 ? librariesNames.size() - 1 : index - 1);
    const auto &toLoad = librariesNames[nextIndex];
    return (loadSharedLibrary<IGameModule>(toLoad, Arcade::GAME));
}

void Arcade::Loader::closeAll()
{
    if (loadGameLibraries)
        dlclose(loadGameLibraries);
    if (loadGraphicLibraries)
        dlclose(loadGraphicLibraries);
    if (loadMenuLibrary)
        dlclose(loadMenuLibrary);
}