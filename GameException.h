#pragma once
#include <string>
#include <stdexcept>

class GameException : public std::exception {
public:
    explicit GameException(const std::string& message) : message(message) {}
    const char* what() const noexcept override { return message.c_str(); }

private:
    std::string message;
};

