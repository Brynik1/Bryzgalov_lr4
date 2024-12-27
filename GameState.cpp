#include "GameState.h"

GameState::GameState(GameField& playerField, GameField& enemyField,
    ShipManager& playerShips, ShipManager& enemyShips,
    AbilityManager& abilityManager)
    : playerField(playerField), enemyField(enemyField),
    playerShips(playerShips), enemyShips(enemyShips),
    abilityManager(abilityManager) {}

void GameState::save(const std::string& filename) {
    playerField.writeInfo("info_player");
    enemyField.writeInfo("info_enemy");
    abilityManager.writeInfo("info_ability");
    abilityManager.loadInfo("info_ability");
}

void GameState::load(const std::string& filename) {
    playerField.loadInfo("info_player", playerShips);
    enemyField.loadInfo("info_enemy", enemyShips);
    abilityManager.loadInfo("info_ability");
}

