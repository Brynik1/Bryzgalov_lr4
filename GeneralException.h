#pragma once
#include "GameException.h"

class GeneralException : public GameException {
public:
    GeneralException(const std::string& message) : GameException(message) {}
};

