#include "Game.h"

Game::Game(int width, int height, const std::vector<int>& shipSizes)
    : field(width, height), shipManager(shipSizes), abilityManager(), enemyShipManager(shipSizes), enemyField(width, height),
state(field, enemyField, shipManager, enemyShipManager, abilityManager) {}


int Game::getShipCount() {
    return shipManager.getCount();
}
int Game::getShipLength(int i) {
    return shipManager.getShip(i).getLength();
}
void Game::placeShip(int x, int y, bool vertical, int i) {
    field.placeShip(shipManager.getShip(i), x, y, vertical, i);
}
bool Game::isWin() {
    return enemyShipManager.allShipDestroyed();
}
bool Game::isLoss() {
    return shipManager.allShipDestroyed();
}
void Game::printPlayerField() {
    field.printField();
}
void Game::printEnemyField() {
    enemyField.printField();
}
void Game::useAbility() {
    abilityManager.applyAbility(enemyField, enemyShipManager);
}
void Game::attack(int x, int y) {
    bool attacked;
    // Check for double damage ability
    if (abilityManager.isDoubleDamage()) {
        enemyField.attack(x, y, enemyShipManager);
        abilityManager.delDoubleDamage();
    }

    // Perform the attack
    attacked = enemyField.attack(x, y, enemyShipManager);
    if (attacked) {
        abilityManager.giveRandomAbility(); // Give a random ability for a successful attack
    }
}
bool Game::haveAbility() {
    return abilityManager.getAbilityCount() > 0;
}
void Game::enemyTurn() {
    std::cout << "\nEnemy turn: ";

    srand(time(NULL));
    int x = rand() % field.getWidth();
    int y = rand() % field.getHeight();
    field.attack(x, y, shipManager);
}

void Game::generateEnemyShips() {
    srand(time(NULL));
    for (int i = 0; i < enemyShipManager.getCount(); ++i) {
        int x = rand() % enemyField.getWidth();
        int y = rand() % enemyField.getHeight();
        bool vertical = rand() % 2;
        try {
            enemyField.placeShip(enemyShipManager.getShip(i), x, y, vertical, i);
        }
        catch (const std::exception& e) {
            --i;
        }
    }
}

void Game::resetEnemyShips() {
    enemyShipManager.restoreAllShips();
    enemyField.removeShipsLocations();
    generateEnemyShips();
}
