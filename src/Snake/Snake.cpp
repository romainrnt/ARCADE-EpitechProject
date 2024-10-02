/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Snake.cpp
*/

#include "Snake.hpp"

extern "C" Arcade::IGameModule *getLibrary()
{
    return (new Arcade::GameSnake());
}

extern "C" Arcade::LibraryType getLibraryType()
{
    return ((Arcade::LibraryType)Arcade::GAME);
}

Arcade::GameSnake::GameSnake()
{
    _deltaTime = 0.0f;
    _score = 0;
    _isGameOver = false;
    _currentDirection = Direction::DIR_RIGHT;
    _nextDirection = Direction::DIR_RIGHT;
    _playerName = "Ce giga bg de Marc";
    _background = new Pixel(50, 50, Arcade::BLACK, 100);
    _map = new Pixel(50, 60, Arcade::GREEN, 74);
    _apple = new Pixel(68, 28, Arcade::RED, 2);
    _titleText = new Text(50, 10, "SNAKE", Arcade::YELLOW);
    _playerNameText = new Text(15, 5, _playerName, Arcade::WHITE);
    _scoreText = new Text(85, 5, "Score: 0", Arcade::WHITE);
    _gameOverText = new Text(50, 50, "GAME OVER", Arcade::RED);
    _restartText = new Text(50, 60, "Press \"R\" to restart", Arcade::WHITE);
    _snake.push_back(new Pixel(52, 60, Arcade::MAGENTA, 2));
    _snake.push_back(new Pixel(50, 60, Arcade::YELLOW, 2));
    _snake.push_back(new Pixel(48, 60, Arcade::YELLOW, 2));
    _snake.push_back(new Pixel(46, 60, Arcade::YELLOW, 2));
    _toAdd = false;
}

Arcade::GameSnake::~GameSnake()
{
    delete(_background);
    delete(_map);
    delete(_apple);
    delete(_titleText);
    delete(_playerNameText);
    delete(_scoreText);
    delete(_gameOverText);
    delete(_restartText);
    _snake.clear();
}

void Arcade::GameSnake::drawGraphics(IDisplayModule *libraryPtr)
{
    libraryPtr->drawPixel(_background);
    libraryPtr->drawPixel(_map);

    if (!_isGameOver) {
        libraryPtr->drawPixel(_apple);
        for (auto it = _snake.begin(); it != _snake.end(); it++)
            libraryPtr->drawPixel(*(it));
    }
    else {
        libraryPtr->drawText(_gameOverText);
        libraryPtr->drawText(_restartText);
    }
    libraryPtr->drawText(_scoreText);
    libraryPtr->drawText(_playerNameText);
    libraryPtr->drawText(_titleText);
}

void Arcade::GameSnake::initializePlayerName(std::string playerName)
{
    _playerName = std::move(playerName);
    delete (_playerNameText);
    _playerNameText = new Text(15, 5, _playerName, Arcade::WHITE);
}

void Arcade::GameSnake::handleEvent(CommandType command, IDisplayModule *libraryPtr)
{
    (void)libraryPtr;

    switch (command) {
        case CommandType::RIGHT:
            if (_currentDirection != Direction::DIR_LEFT)
                _nextDirection = Direction::DIR_RIGHT;
            break;
        case CommandType::LEFT:
            if (_currentDirection != Direction::DIR_RIGHT)
                _nextDirection = Direction::DIR_LEFT;
            break;
        case CommandType::UP:
            if (_currentDirection != Direction::DIR_DOWN)
                _nextDirection = Direction::DIR_UP;
            break;
        case CommandType::DOWN:
            if (_currentDirection != Direction::DIR_UP)
                _nextDirection = Direction::DIR_DOWN;
            break;
        case CommandType::R:
            resetGame();
            break;
        default:
            break;
    }
}

void Arcade::GameSnake::updateGameState(double time)
{
    _deltaTime += time;
    double updateInterval = 1.0f / (5.0f + 0.1f * _score);

    if (_deltaTime >= updateInterval && !_isGameOver) {
        _currentDirection = _nextDirection;
        _deltaTime = 0;
        for (size_t i = _snake.size() - 1; i > 0; i--) {
            _snake[i]->setXCoordinate(_snake[i - 1]->getXCoordinate());
            _snake[i]->setYCoordinate(_snake[i - 1]->getYCoordinate());
        }
        if (_toAdd) {
            Pixel *tmp = new Pixel(_snake.back()->getXCoordinate(), _snake.back()->getYCoordinate(), Arcade::Color::GREEN, 2);
            _snake.push_back(tmp);
            _toAdd = false;
        }
        int headX = _snake.front()->getXCoordinate();
        int headY = _snake.front()->getYCoordinate();
        if (_currentDirection == Direction::DIR_RIGHT)
            _snake.front()->setXCoordinate(headX + 2);
        else if (_currentDirection == Direction::DIR_LEFT)
            _snake.front()->setXCoordinate(headX - 2);
        else if (_currentDirection == Direction::DIR_UP)
            _snake.front()->setYCoordinate(headY - 2);
        else if (_currentDirection == Direction::DIR_DOWN)
            _snake.front()->setYCoordinate(headY + 2);
        checkAppleCollision();
        checkGameOver();
    }
}

bool Arcade::GameSnake::checkCoordinates(int x, int y)
{
    for (const auto &segment : _snake) {
        if (x == segment->getXCoordinate() && y == segment->getYCoordinate())
            return (false);
    }
    return (true);
}

void Arcade::GameSnake::checkAppleCollision()
{
    int x;
    int y;

    if (_snake.front()->getXCoordinate() == _apple->getXCoordinate() && _snake.front()->getYCoordinate() == _apple->getYCoordinate()) {
        _toAdd = true;
        _score += 1;
        _scoreText->setTextString("score : " + std::to_string(_score));
        srand(static_cast<unsigned>(time(0)));
        do {
            x = (rand() % 73) + 14;
            y = (rand() % 73) + 24;
            if (x % 2 != 0) {
                if (x < 86) {
                    x++;
                } else {
                    x--;
                }
            }
            if (y % 2 != 0) {
                if (y < 86) {
                    y++;
                } else {
                    y--;
                }
            }
        } while (!checkCoordinates(x, y));
        _apple->setXCoordinate(x);
        _apple->setYCoordinate(y);
    }
}

void Arcade::GameSnake::checkGameOver()
{
    int headX = _snake.front()->getXCoordinate();
    int headY = _snake.front()->getYCoordinate();
    bool isOutOfBound = headX < 14 || headX > 86 || headY < 24 || headY > 96;

    if (isOutOfBound)
        _isGameOver = true;
    else {
        for (auto it = _snake.begin() + 1; it != _snake.end(); it++) {
            if (headX == (*it)->getXCoordinate() && headY == (*it)->getYCoordinate()) {
                _isGameOver = true;
                break;
            }
        }
    }
}

void Arcade::GameSnake::resetGame()
{
    _deltaTime = 0.0f;
    _score = 0;
    _isGameOver = false;
    _currentDirection = Direction::DIR_RIGHT;
    _nextDirection = Direction::DIR_RIGHT;
    _scoreText->setTextString("score : " + std::to_string(_score));
    for (auto &segment : _snake) {
        delete segment;
    }
    _snake.clear();
    _snake.push_back(new Pixel(52, 60, Arcade::MAGENTA, 2));
    _snake.push_back(new Pixel(50, 60, Arcade::GREEN, 2));
    _snake.push_back(new Pixel(48, 60, Arcade::GREEN, 2));
    _snake.push_back(new Pixel(46, 60, Arcade::GREEN, 2));
}