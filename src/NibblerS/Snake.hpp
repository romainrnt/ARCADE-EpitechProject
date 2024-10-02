/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Snake.hpp
*/

#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "../../include/IGameModule.hpp"
#include "../../include/IDisplayModule.hpp"

namespace Arcade {
    class GameSnake : public IGameModule {
        public:
            GameSnake();
            ~GameSnake() override;
            void initializePlayerName(std::string playerName) override;
            void drawGraphics(IDisplayModule *libraryPtr) override;
            void handleEvent(CommandType cmd, IDisplayModule *libraryPtr) override;
            void updateGameState(double timeElapsed) override;
            bool checkCoordinates(int x, int y);
            void checkAppleCollision();
            void checkGameOver();
            void resetGame();
            void checkWall();
        private:
            Pixel *_background;
            Pixel *_map;
            std::string _playerName;
            std::vector<Pixel *> _snake;
            std::vector<Pixel *> _bgb;
            bool _toAdd;
            Pixel *_apple;
            int _score;
            Text *_scoreText;
            Text *_playerNameText;
            Text *_titleText;
            Text *_gameOverText;
            Text *_restartText;
            double _deltaTime;
            bool _isGameOver;
            enum Direction {
                DIR_LEFT,
                DIR_RIGHT,
                DIR_UP,
                DIR_DOWN
            };
            Direction _currentDirection;
            Direction _nextDirection;
    };
    IDisplayModule *getLibrary();
    LibraryType getLibraryType();
}