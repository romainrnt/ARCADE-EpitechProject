/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Exceptions.cpp
*/

#include "Exceptions.hpp"

Error::Error(const std::string &msg) noexcept : _msg(msg)
{
    printError();
}

Error::~Error()
{}

void Error::printError() noexcept
{
    std::cerr << "Error: " << _msg << std::endl;
}