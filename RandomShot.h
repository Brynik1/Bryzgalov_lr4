#pragma once
#include "Ability.h"
#include <random>

class RandomShot : public Ability {
public:
    bool apply(GameField& field, ShipManager& manager) override;
    std::string getName() const override { return "RandomShot"; }
};