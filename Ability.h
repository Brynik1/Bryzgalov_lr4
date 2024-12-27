#pragma once
#include "GameField.h"
#include "ShipManager.h"

class Ability {
public:
	virtual bool apply(GameField& field, ShipManager& manager) = 0;
	virtual std::string getName() const = 0;
	virtual ~Ability() = default;
};