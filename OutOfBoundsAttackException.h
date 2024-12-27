#pragma once
#include "GameException.h"

class OutOfBoundsAttackException : public GameException {
public:
    OutOfBoundsAttackException() : GameException("Attack coordinates out of bounds.") {}
};

