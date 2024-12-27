#pragma once
#include "Ability.h"

class Scanner : public Ability {
public:
	bool apply(GameField& field, ShipManager& manager) override;
	std::string getName() const override { return "Scanner"; }
};