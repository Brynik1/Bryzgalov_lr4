#include <iostream>
#include <vector>
#include <stdexcept>
#include "ShipManager.h"
#include "GameField.h"
#include "AbilityManager.h"
#include "DefaultInputHandler.h"
#include "GameControl.h"
#include "Game.h"
#include "Ship.h"

int main() {
    //ShipManager manager({ 1 });
    //manager.writeInfo("info");
    //manager.loadInfo("info");
    //Ship ship(4);
    //std::ofstream out("info");
    //ship.writeInfo(out);
    //out.close();
    //std::ifstream in("info");
    //ship.printFile(in);
    //ship.loadInfo(in);
    //std::cout << ship.getLength() << "\n";
    //std::cout << ship.isDestroyed();
    //AbilityManager manager;
    //manager.giveRandomAbility();
    //std::cout << manager.getAbilityCount() << std::endl;
    //manager.writeInfo("info");
    //manager.loadInfo("info");
    //manager.writeInfo("info");




    //ShipManager manager({ 2,2 });
    //Ship new_ship(3);
    //manager.addShip(new_ship);
    //GameField field(10, 10);


    //Ship& ship0 = manager.getShip(0);
    //field.placeShip(ship0, 1, 1, true, 0);
    //Ship& ship1 = manager.getShip(1);
    //field.placeShip(ship1, 1, 4, false, 1);
    //Ship& ship2 = manager.getShip(2);
    //field.placeShip(ship2, 1, 6, false, 2);
    //field.attack(2, 4, manager);
    //field.attack(2, 4, manager);
    //field.attack(1, 4, manager);
    //field.attack(1, 4, manager);

    //field.writeInfo("info");
    //field.printField();


    //field.loadInfo("info", manager);

    //field.printField();
    //std::cout << "\n" << manager.getCount();
    //std::cout << "\nDestroed: " << manager.getShip(1).isDestroyed();

    //field.writeInfo("new_info");







    //int width = 10, height = 10;
    //std::vector<int> sizes = { 2,3 };
    //ShipManager manager(sizes);
    //GameField field(width, height);


    //Ship& ship1 = manager.getShip(0);
    //field.placeShip(ship1, 0, 0, false, 0); // Place horizontally
    //Ship& ship2 = manager.getShip(1);
    //field.placeShip(ship2, 2, 4, true, 1); // Place verticaly

    //field.attack(1, 0, manager);
    //field.attack(1, 0, manager);
    //field.writeInfo("info");
    
    //ShipManager ships({ 1,2,3,4 });
    //ships.writeInfo("info");

    //std::cout << "Enter field size (width height): ";
    //std::cin >> width >> height;
    std::setlocale(LC_ALL, "en_US.UTF-8");
    while (true) {
        Game game(10, 10, { 1, 1, 1, 1, 2, 2, 2, 3, 3, 4 });
        DefaultInputHandler inputHandler;
        GameControl<DefaultInputHandler> gameControl(game, std::move(inputHandler));
        gameControl.gameCycle();
    }

    return 0;
}

