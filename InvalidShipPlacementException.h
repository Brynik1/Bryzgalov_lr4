#pragma once
#include "GameException.h"

class InvalidShipPlacementException : public GameException {
public:
    InvalidShipPlacementException(const std::string& reason) : GameException("Invalid ship placement: " + reason) {}
};

