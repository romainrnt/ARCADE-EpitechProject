/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-pierre.maurer
** File description:
** Exceptions.hpp
*/

#pragma once
#include <exception>
#include <string>
#include <iostream>

class Error : public std::exception {
    public:
        Error(const std::string &msg) noexcept;
        ~Error();
        const char *what() const noexcept override { return _msg.data(); }
        void printError() noexcept;
    protected:
        std::string _msg;
};