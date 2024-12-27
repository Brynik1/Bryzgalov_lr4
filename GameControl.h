#pragma once
#include "Game.h"
#include "FieldTracking.h"


template <typename InputHandler>
class GameControl {

public:
    GameControl(Game& game, InputHandler&& inputHandler)
        : game(game), inputHandler(inputHandler), renderer() {}

    void gameCycle() {
        FieldTracking<FieldRenderer> fieldTracking(game.getPlayerField(), game.getEnemyField(), renderer);

        // Ask the player if they want to load a saved game
        std::cout << "Would you like to load a saved game? ";
        bool flag_loadGame = inputHandler.loadGameFlag();

        if (flag_loadGame) {
            game.loadGame();
        }
        else {
            placeShips();
        }

        std::cout << "\nThe game has started!\n";
        while (true) {
            std::cout << std::endl;
            fieldTracking.printFields();

            playerTurn();
            if (!game.isWin()) {
                game.enemyTurn();
            }

            // Check if the player has won or lost
            if (game.isWin()) {
                std::cout << "\nYour turn: F9 + ???\n";
                std::cout << "Congratulations! You won this round!\n\n";
                std::cout << "Starting a new round...\n";
                game.resetEnemyShips();
            }
            else if (game.isLoss()) {
                std::cout << "\nEnemy turn: F9 + ???\n";
                std::cout << "Game over! You have lost.\n\n";
                std::cout << "Starting a new game...\n";
                break;
            }
        }
    }

private:
    Game& game;
    InputHandler& inputHandler;
    FieldRenderer renderer;

    void placeShips() {
        FieldTracking<FieldRenderer> fieldTracking(game.getPlayerField(), game.getEnemyField(), renderer);
        std::cout << "Time to place your ships:\n";
        for (int i = 0; i < game.getShipCount(); ++i) {
            int x, y;
            bool vertical = true;

            std::cout << "Place your ship of length " << game.getShipLength(i) << ". ";
            std::tie(x, y) = inputHandler.getAttackCoordinates();

            // Ask if the ship should be placed vertically if it has a length greater than 1
            if (game.getShipLength(i) > 1) {
                std::cout << "Should the ship be placed vertically? ";
                vertical = inputHandler.loadGameFlag();
            }

            // Attempt to place the ship and handle any exceptions
            try {
                //field.placeShip(shipManager.getShip(i), x, y, vertical, i);
                game.placeShip(x, y, vertical, i);
                std::cout << std::endl;
                fieldTracking.printFields();
                std::cout << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\nPlease try again.\n";
                --i; // Decrease index to repeat placement
            }

        }
        game.generateEnemyShips();
    }

    void playerTurn() {
        std::cout << "\nYour turn:\n";

        // Variable for player's action choice
        int actionChoice = 0;

        // Check if there are available abilities
        if (game.haveAbility()) {
            actionChoice = inputHandler.getActionChoice();
        }
        else {
            actionChoice = inputHandler.getActionChoiceNoAbility();
        }

        // Handle the action choice
        switch (actionChoice) {
        case 1: // Use Ability
            try {
                game.useAbility();
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
                playerTurn();
            }
            break;

        case 0: // Attack
        {
            int x, y;
            try {
                std::cout << "Attack! ";
                std::tie(x, y) = inputHandler.getAttackCoordinates();
                game.attack(x, y);
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
                playerTurn();
            }
            break;
        }

        case 2: // Save Game
            game.saveGame();
            std::cout << "Game successfully saved.\n";
            playerTurn();
            break;

        case 3: // Load game
            try {
                game.loadGame();
                std::cout << "Game loaded successfully.\n";
            }
            catch(const std::exception & e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            playerTurn();
            break;

        default:
            std::cout << "Invalid choice, form again!\n";
            playerTurn();
        }
    }
};
