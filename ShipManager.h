#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Ship.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;


class ShipManager {
public:
    ShipManager(const std::vector<int>& sizes);
    Ship& getShip(int index);
    int getCount();
    int getShipIndex(const Ship& ship) const;
    bool allShipDestroyed();
    void restoreAllShips();
    void removeAllShips();
    void addShip(Ship& ship);
    void writeInfo(const std::string& filename);
    void loadInfo(const std::string& filename);

    //void toJson(const std::string& filename) const;
    //void fromJson(const std::string& filename);


private:
    std::vector<Ship> ships;
};

