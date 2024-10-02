/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Core.hpp
*/

#pragma once
#include <string>
#include <vector>
#include <map>
#include <array>
#include <chrono>
#include <fstream>
#include <algorithm>
#include "../../include/IDisplayModule.hpp"
#include "../../include/IGameModule.hpp"
#include "../../include/IType.hpp"
#include "../Tools/Loader/Loader.hpp"
#include "../Tools/Text/Text.hpp"
#include "../Tools/Pixel/Pixel.hpp"
#include "../../include/IDisplayMenu.hpp"

namespace Arcade {
    class Core {
    public:
        Core() : _graphicLibrary(nullptr), _gameLibrary(nullptr) {}
        ~Core() {};
        void assignGraphicLibrary(IDisplayModule *graphicLibrary);
        void assignGameLibrary(IGameModule *gameLibrary);
        inline IDisplayModule *getGraphicLibrary() const {return (_graphicLibrary);};
        inline IGameModule *getGameLibrary() const {return (_gameLibrary);};
        void ChangeLibrary(Loader &loader, CommandType event);
        bool GameLoop(Loader &loader, std::string &playerName);
        std::string playerNameInputLoop(Arcade::Loader &loader, Arcade::IDisplayMenu *menu);
        void deleteLibraries();
        const std::string &getGameName() const {return _gameName;};
        void assignGameName(const std::string &nameGame);
    private:
        IDisplayModule *_graphicLibrary;
        IGameModule *_gameLibrary;
        std::string _gameName;
        std::string _playerName;
        std::map<CommandType, int> CoreKeyMap {
            {A, 'a'},
            {B, 'b'},
            {C, 'c'},
            {D, 'd'},
            {E, 'e'},
            {F, 'f'},
            {G, 'g'},
            {H, 'h'},
            {I, 'i'},
            {J, 'j'},
            {K, 'k'},
            {L, 'l'},
            {M, 'm'},
            {N, 'n'},
            {O, 'o'},
            {P, 'p'},
            {Q, 'q'},
            {R, 'r'},
            {S, 's'},
            {T, 't'},
            {U, 'u'},
            {V, 'v'},
            {W, 'w'},
            {X, 'x'},
            {Y, 'y'},
            {Z, 'z'},
            {NUM0, '0'},
            {NUM1, '1'},
            {NUM2, '2'},
            {NUM3, '3'},
            {NUM4, '4'},
            {NUM5, '5'},
            {NUM6, '6'},
            {NUM7, '7'},
            {NUM8, '8'},
            {NUM9, '9'},
            {SPACE, ' '},
        };
    };
}