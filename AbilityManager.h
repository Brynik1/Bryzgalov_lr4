#pragma once
#include <vector>
#include <queue>
#include <random>
#include "Ability.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "RandomShot.h"
#include "NoAbilitiesException.h"
#include <fstream>

class AbilityManager {
public:
    AbilityManager();
    void applyAbility(GameField& field, ShipManager& manager);
    void addAbility(Ability* ability);
    void generateInitialAbilities();
    void giveRandomAbility();
    int getAbilityCount();
    bool isDoubleDamage();
    void delDoubleDamage();
    void writeInfo(const std::string& filename);
    void loadInfo(const std::string& filename);


private:
    bool doubleDamage = false;
    std::queue<Ability*> abilities;
};