#pragma once

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "GameField.h"
#include "ShipManager.h"
#include "AbilityManager.h"

class GameState {
public:
    GameField& playerField;
    GameField& enemyField;
    ShipManager& playerShips;
    ShipManager& enemyShips;
    AbilityManager& abilityManager;

    GameState(GameField& playerField, GameField& enemyField,
        ShipManager& playerShips, ShipManager& enemyShips,
        AbilityManager& abilityManager);

    void save(const std::string& filename); // Сохранение состояния игры в файл
    void load(const std::string& filename); // Загрузка состояния игры из файла

};



