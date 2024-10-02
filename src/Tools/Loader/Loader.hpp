/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Loader.hpp
*/

#pragma once
#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "filesystem"
#include <algorithm>
#include "../../../include/IGameModule.hpp"
#include "../../../include/IDisplayModule.hpp"
#include "../../../include/IType.hpp"
#include "../Errors/Exceptions.hpp"

namespace Arcade {
    class Loader {
    public:
        Loader() : loadMenuLibrary(nullptr), loadGraphicLibraries(nullptr), loadGameLibraries(nullptr) {};
        virtual ~Loader();
        template<typename T>
        T *loadSharedLibrary(std::string const &fp, LibraryType type) {
            void *sharedLib = dlopen(fp.c_str(), RTLD_NOW);
            if (!sharedLib) {
                throw Error("Failed to load shared library: " + std::string(dlerror()));
            }
            Arcade::LibraryType (*getType)() = reinterpret_cast<Arcade::LibraryType (*)()>(dlsym(sharedLib, "getLibraryType"));
            if (!getType) {
                throw Error("Failed to get function symbol: " + std::string(dlerror()));
                dlclose(sharedLib);
                return (nullptr);
            }
            if (getType() != type) {
                throw Error("The loaded library has an incorrect type");
                dlclose(sharedLib);
                return (nullptr);
            }
            T *(*getLibrary)() = reinterpret_cast<T*(*)()>(dlsym(sharedLib, "getLibrary"));
            if (!getLibrary) {
                throw Error("Failed to get function symbol: " + std::string(dlerror()));
                dlclose(sharedLib);
                return (nullptr);
            }
            switch (type) {
                case MENU:
                    if (loadMenuLibrary) dlclose(loadMenuLibrary);
                    loadMenuLibrary = sharedLib;
                    break;
                case GRAPHIC:
                    if (loadGraphicLibraries) dlclose(loadGraphicLibraries);
                    loadGraphicLibraries = sharedLib;
                    loadGraphicsName = fp;
                    break;
                case GAME:
                    if (loadGameLibraries) dlclose(loadGameLibraries);
                    loadGameLibraries = sharedLib;
                    loadGameName = fp;
                    break;
                default:
                    throw Error("Invalid library type.");
                    dlclose(sharedLib);
                    return (nullptr);
            }
            return (getLibrary());
        }
        std::vector<std::pair<std::string, std::string>> getAvailableLibraries(Arcade::LibraryType type);
        std::string getLibraryName(std::basic_string<char> filePath);
        IDisplayModule *loadNextGraphicLibrary(bool direction);
        IGameModule *loadNextGameLibrary(bool direction);
        void closeAll();
    private:
        void *loadMenuLibrary;
        void *loadGraphicLibraries;
        void *loadGameLibraries;
        std::string loadGraphicsName;
        std::string loadGameName;
    };
}