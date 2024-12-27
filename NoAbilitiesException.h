#pragma once
#include "GameException.h"

class NoAbilitiesException : public GameException {
public:
    NoAbilitiesException() : GameException("No abilities available.") {}
};

