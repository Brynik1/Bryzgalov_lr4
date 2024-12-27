#pragma once
#include "GameField.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include "GameState.h"

class Game {
public:
    Game(int width, int height, const std::vector<int>& shipSizes);
    void startGame();
    void loadGame() {
        state.load("info");
    }
    void saveGame() {
        state.save("info");
    }
    bool isWin();
    bool isLoss();
    void resetEnemyShips();
    void enemyTurn();
    void printPlayerField();
    void printEnemyField();
    void useAbility();
    void attack(int x, int y);
    bool haveAbility();
    void placeShip(int x, int y, bool vertical, int i);
    void generateEnemyShips();
    GameField& getPlayerField() {
        return field;
    }
    GameField& getEnemyField() {
        return enemyField;
    }
    int getShipLength(int i);
    int getShipCount();


private:

    GameField field;
    ShipManager shipManager;
    AbilityManager abilityManager;

    GameField enemyField;
    ShipManager enemyShipManager;
    GameState state;
};
